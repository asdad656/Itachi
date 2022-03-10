/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 15:32:32
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 18:45:17
 * @Description: 
 */

#ifndef __EVENTLOOP__H__
#define __EVENTLOOP__H__
#include <vector>
#include <memory>

#include <mutex>
#include "noncopyaable.h"
// #include<
namespace Itachi
{
    class Channel;
    class Poller;
    class EventLoop : public nonCopyable
    {
    public:
        using ActivateChannels = std::vector<Channel*>;
        using ExtraTask = std::function<void(void)>;
        using ExtraTasks = std::vector<ExtraTask>;
        using ExtraTasks_ptr = std::shared_ptr<ExtraTasks>;
        EventLoop();
        ~EventLoop();
        void loop();
        void stop();
        bool isInLoopThread() const;
        void runInLoop(ExtraTask cb);
        void queueInLoop(ExtraTask cb);
        void update(Channel *);
        void removeChannel(Channel*);
    private:
        void doExtraTasks();
        void assertInLoopThread() const;
        void weakUp();
        void headReadOnWeakUpFd();
    private:
        bool m_isLooping;
        bool m_stop;
        ExtraTasks m_extraTasks;
        std::mutex m_mutex;
        std::unique_ptr<Poller> m_poller;
        ActivateChannels m_activeChannels;
        int m_weakUpFd;
        std::unique_ptr<Channel>m_weakUpChannle;
        bool  m_isdoingExtraTasks;
    };
}

#endif