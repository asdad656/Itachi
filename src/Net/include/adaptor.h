/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-09 15:59:18
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 09:14:17
 * @Description: 
 */
#ifndef __ADAPTOR___H__
#define __ADAPTOR___H__
#include "callback.h"
#include<functional>
struct sockaddr_in;
namespace Itachi
{
    class Channel;
    class EventLoop;
    class Socket;
    class Aadaptor
    {
    public:
        Aadaptor(EventLoop *ownerLoop,
                    sockaddr_in *localaddr
                    );
        ~Aadaptor();

        void setReadCallBack(AdaptorReadCallBack cb)
        {
            m_readCallBack = std::move(cb);
        }
        void setTcpNoDealy(bool);
        const sockaddr_in*getLocalAddr();
        void listen();
    private:
        void handleRead();
    private:
        bool m_listening;
        int m_fd;
        EventLoop *m_ownerLoop;
        Channel *m_channel;
        AdaptorReadCallBack m_readCallBack;
        std::unique_ptr<Socket>m_socket;
    };
}

#endif