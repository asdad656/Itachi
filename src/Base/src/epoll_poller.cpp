/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-08 14:41:06
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-08 16:45:20
 * @Description: 
 */
#include "epoll_poller.h"
#include "definition.h"
#include "config.h"
#include "channel.h"
#include <sys/epoll.h>
namespace Itachi
{
    static const int EPOLL_WAIT_TIMEOUT = 1000000;
    EpollPoller::EpollPoller(EventLoop *ownerLoop, const size_t &maxEeollSize) : Poller(ownerLoop),
                                                                                        m_maxEpollSize(maxEeollSize),
                                                                                        m_epollRs(m_maxEpollSize)
    {
        m_fd = epoll_create(m_maxEpollSize);
        if (m_fd < 0)
        {
            LOG_FATAL << "epoll_create faild in construct of EpollPoller";
        }
    }
    EpollPoller::~EpollPoller()
    {
        LOG_INFO << "EpollPoller Exit!";
        close(m_fd);
    }
    void EpollPoller::fillActivateChannles(ActivateChannels &activateChannels,int count)
    {
        for (const auto &val : m_epollRs)
        {
            auto it = m_channels.find(val.data.fd);
            ASSERT(it != m_channels.end());
            // ASSERT(it->second < m_channels.size());
            std::unique_ptr<Channel> &ptr = it->second;
            if (ptr->getEvent() & val.events)
            {
                ptr->setRevent(ptr->getEvent() & val.events);
            }
            activateChannels.push_back(ptr.get());
            if(--count==0){
            break;
        }
        }
  
    }
    void EpollPoller::poll(ActivateChannels &activateChannels)
    {
        int rt = epoll_wait(m_fd, &*m_epollRs.begin(), m_maxEpollSize, EPOLL_WAIT_TIMEOUT);
        if (rt < 0)
        {
            LOG_FATAL << "epoll_wait ERROR!!!!   rt<0!!!!!!";
        }
        else if (rt > 0)
        {
            fillActivateChannles(activateChannels,rt);
        }
        else
        {
            LOG_INFO << "nothing happend";
        }
    }
    void EpollPoller::update(Channel *channel)
    {
        ASSERT(channel != nullptr);
        int index = channel->getIndex();
        int fd = channel->getFd();
        if (index < 0)
        {
            ASSERT(m_channels.find(fd) == m_channels.end());
            struct epoll_event event;
            memset(&event, 0, sizeof(struct epoll_event));
            event.events = channel->getEvent();
            event.data.fd = fd;
            int rt = epoll_ctl(m_fd, EPOLL_CTL_ADD, fd, &event);
            if (rt != 0)
            {
                LOG_FATAL << "EPOLL_CTL_ADD faild on epollfd: " << m_fd << "   fd:" << fd;
            }
            channel->setIndex(m_channels.size());
            m_channels[fd].reset(channel);
        }
        else
        {
            ASSERT(m_channels.find(fd) != m_channels.end());
            ASSERT(m_channels[fd].get() == channel);
            if (channel->hasNoneEvent())
            {
                int rt = epoll_ctl(m_fd, EPOLL_CTL_DEL, fd, NULL);
                if (rt != 0)
                {
                    LOG_FATAL << "EPOLL_CTL_DEL faild on epollfd: " << m_fd << "   fd:" << fd;
                }
                m_channels.erase(fd);
                channel->setIndex(-1);
            }
            else
            {
                struct epoll_event event;
                memset(&event, 0, sizeof(struct epoll_event));
                event.events = channel->getFd();
                event.data.fd = fd;
                int rt = epoll_ctl(m_fd, EPOLL_CTL_MOD,fd, &event);
                if (rt != 0)
                {
                    LOG_FATAL << "EPOLL_CTL_MOD faild on epollfd: " << m_fd << "   fd:" << fd;
                }
            }
        }
    }
}