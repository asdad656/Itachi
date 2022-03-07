/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 15:32:42
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 20:59:11
 * @Description: 
 */
#include "EventLoop.h"
#include "channel.h"
#include "definition.h"
#include <sys/epoll.h>

namespace Itachi
{
    static thread_local EventLoop *thread_t_eventLoop = nullptr;
    EventLoop::EventLoop() : m_isLooping(false),
                             m_stop(true),
                             m_extraTasks(new ExtraTasks)
    {
        ASSERT(thread_t_eventLoop == nullptr);
        thread_t_eventLoop = this;
    }
    EventLoop::~EventLoop()
    {
        ASSERT(!m_isLooping);
    }
    void EventLoop::loop()
    {
        while (true)
        {
        }
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

    void EventLoop::runInLoop(const ExtraTask &cb)
    {
        if (isInLoopThread())
        {
            cb();
        }
        else
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (!m_extraTasks.unique())
            {
                m_extraTasks.reset(new ExtraTasks(*m_extraTasks.get()));
            }
            ASSERT(m_extraTasks.unique());
            m_extraTasks->emplace_back(cb);
        }
    }

    void EventLoop::doExtraTasks()
    {
        ExtraTasks_ptr m_tasks = nullptr;
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_tasks = m_extraTasks;
            ASSERT(!m_tasks.unique());
        }
        while (m_tasks->size() != 0)
        {
            m_tasks->back()();
            m_tasks->pop_back();
        }
    }

    void EventLoop::update(Channel *channel)
    {
        ASSERT(channel != nullptr);
        if (channel != nullptr)
            if (channel->getIndex() < 0)
            {
                ASSERT(m_channelMap.find(channel->getFd()) == m_channelMap.end());
            }
            else
            {
            }
    }
}