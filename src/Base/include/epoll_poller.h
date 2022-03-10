/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-08 14:38:20
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 17:38:31
 * @Description: 
 */
#ifndef __EPOLL__POLER__H__
#define __EPOLL__POLER__H__
#include "poller.h"
#include<vector>
struct epoll_event;
namespace Itachi{
    class EventLoop;
    class EpollPoller : public Poller{
    public:
        using EpollRs=std::vector<epoll_event>;
        EpollPoller(EventLoop*ownerLoop,const size_t&maxEeollSize=1000);
        ~EpollPoller();
        void fillActivateChannles(ActivateChannels&,int) override;
        void poll(ActivateChannels&)override ;
        void update(Channel *)override;
        void removeChannel(Channel*)override;
    private:
        size_t m_maxEpollSize;
        EpollRs m_epollRs;
    };
}






#endif