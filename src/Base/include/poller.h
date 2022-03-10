/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 20:56:07
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 20:25:44
 * @Description: 
 */
#ifndef __POLLER__H__
#define __POLLER__H__
#include <map>
#include <vector>
#include<memory>
namespace Itachi
{
    class Channel;
    class EventLoop;
    class Poller
    {
    public:
        using Channels = std::map<int,Channel*>;
        using ActivateChannels = std::vector<Channel*>;
        Poller(EventLoop *ownerLoop):
        m_fd(-1),
        m_ownerLoop(ownerLoop)
        {
        }
        virtual ~Poller() {
            
        }
        virtual void fillActivateChannles(ActivateChannels&,int) = 0;
        virtual void poll(ActivateChannels&) = 0;
        virtual void update(Channel *)=0;
        virtual void removeChannel(Channel*)=0;
    protected:
        int m_fd;
        EventLoop *m_ownerLoop;
        Channels m_channels;
    };
}

#endif