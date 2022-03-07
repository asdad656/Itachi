/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 15:32:32
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 20:58:30
 * @Description: 
 */

#ifndef __EVENTLOOP__H__
#define __EVENTLOOP__H__
#include<vector>
#include<memory>
#include<map>
#include<mutex>
#include"noncopyaable.h"
// #include<

namespace Itachi{
    class Channel;
    class Poller;
    class Adaptor;
    class EventLoop : public nonCopyable{
        public:
        using Channels=std::vector<std::unique_ptr<Channel>>;
        using ChannelMap=std::map<int,size_t>;
        using ExtraTask=std::function<void(void)>;
        using ExtraTasks=std::vector<ExtraTask>;
        using ExtraTasks_ptr=std::shared_ptr<ExtraTasks>;
        EventLoop();
        ~EventLoop();
        void loop();
        void stop();
        bool isInLoopThread()const;
        void runInLoop(const ExtraTask& cb);
        void update(Channel*);
        private:
        void doExtraTasks();
        void assertInLoopThread()const;
        private:
            Channels m_channels;
            ChannelMap m_channelMap;
            bool m_isLooping;
            bool m_stop;
            ExtraTasks_ptr m_extraTasks;
            std::mutex m_mutex;
            std::unique_ptr<Poller>m_poller;
    };
}


#endif