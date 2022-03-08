/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 15:32:42
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-08 18:07:28
 * @Description: 
 */
#include "EventLoop.h"
#include "channel.h"
#include "definition.h"
#include <sys/epoll.h>
#include "poller.h"
#include"epoll_poller.h"
#include<sys/eventfd.h>
#include<unistd.h>
namespace Itachi
{
    static int creaateEventFd(){
        int fd=eventfd(0,EFD_NONBLOCK | EFD_CLOEXEC);
        if(fd<0){
            LOG_ERROR<<"creaateEventFd failed";
            return 0;
        }
        return fd;
    }
    static thread_local EventLoop *thread_t_eventLoop = nullptr;
    EventLoop::EventLoop() : m_isLooping(false),
                             m_stop(true),
                             m_extraTasks(),
                             m_poller(new EpollPoller(this)),
                             m_weakUpFd(creaateEventFd()),
                             m_weakUpChannle(new Channel(this,m_weakUpFd)),
                             m_isdoingExtraTasks(false)
    {
        ASSERT(thread_t_eventLoop == nullptr);
        thread_t_eventLoop = this;
        m_weakUpChannle->setReadCallback(
            std::bind(&EventLoop::headReadOnWeakUpFd,this));
        m_weakUpChannle->enableRead();
    }
    EventLoop::~EventLoop()
    {
        ASSERT(!m_isLooping);
    }
    void EventLoop::loop()
    {
        m_isLooping=true;
        while (m_stop)
        {
            m_activeChannels.clear();
            m_poller->poll(m_activeChannels);
            for(auto&val:m_activeChannels){
                val->handle();
            }
            doExtraTasks();
        }
        m_isLooping=false;
    }
    void EventLoop::stop()
    {
        m_stop = true;
    }
    bool EventLoop::isInLoopThread() const
    {
        return thread_t_eventLoop == this;
    }
    void EventLoop::assertInLoopThread() const
    {
        ASSERT(isInLoopThread());
    }

    void EventLoop::runInLoop(ExtraTask cb)
    {
        if (isInLoopThread())
        {
            cb();
        }
        else
        {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_extraTasks.push_back(std::move(cb));
            }
        }
        if(!isInLoopThread()||m_isdoingExtraTasks||!m_isLooping){
            weakUp();
        }
    }

    void EventLoop::doExtraTasks()
    {
        m_isdoingExtraTasks=true;
        ExtraTasks m_tasks;
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_tasks.swap(m_extraTasks);
        }
        for(auto&val:m_tasks){
            val();
        }
        m_isdoingExtraTasks=false;
    }

    void EventLoop::update(Channel *channel)
    {
        ASSERT(channel != nullptr);
        m_poller->update(channel);
        // if (channel != nullptr)
        //     if (channel->getIndex() < 0)
        //     {
        //         //ASSERT(m_channelMap.find(channel->getFd()) == m_channelMap.end());
        //     }
        //     else
        //     {
        //     }
    }

    void EventLoop::weakUp(){
        int64_t c=1;
        int rt=write(m_weakUpFd,static_cast<void*>(&c),sizeof(int64_t));
        if(rt!=sizeof(int64_t)){
            LOG_ERROR<<"weakUp error!!";
        }
    }

    void EventLoop::headReadOnWeakUpFd(){
        int64_t c;
        int rt=read(m_weakUpFd,static_cast<void*>(&c),sizeof(int64_t));
        if(rt!=sizeof(int64_t)){
            LOG_ERROR<<"headReadOnWeakUpFd error!!";
        }
    }   
    }