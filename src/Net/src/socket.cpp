/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-06 16:22:33
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 17:06:44
 * @Description: 
 */
#include "socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "definition.h"
namespace Itachi
{
    void Socket::setNoBlock(const bool &val)
    {
        int opt = val ? 1 : 0;
        int rt = setsockopt(m_fd, SOL_SOCKET, SOCK_NONBLOCK, &opt, sizeof(int));
        if (rt)
        {
            LOG_ERROR << "setNoBlock error";
        }
    }

    void Socket::setReuseAddr(const bool &val)
    {
        int opt = val ? 1 : 0;
        int rt = setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
        if (rt)
        {
            LOG_ERROR << "setReuseAddr error";
        }
    }

    void Socket::setReusePort(const bool &val)
    {
        int opt = val ? 1 : 0;
        int rt = setsockopt(m_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(int));
        if (rt)
        {
            LOG_ERROR << "setReusePort error";
        }
    }

    void Socket::setTcpNoDelay(const bool &val)
    {

        int opt = val ? 1 : 0;
        int rt = setsockopt(m_fd, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(int));

        if (rt)
        {
            LOG_ERROR << "setTcpNoDelay error";
        }
    }
    void Socket::setSendTimeOut(const int &val)
    {
        int opt = val ? 1 : 0;
        int rt = setsockopt(m_fd, SOL_SOCKET, SO_SNDTIMEO, &opt, sizeof(int));
        if (rt)
        {
            LOG_ERROR << "setSendTimeOut error";
        }
    }
    void Socket::setRecvTieOut(const int &val)
    {
        int opt = val ? 1 : 0;
        int rt = setsockopt(m_fd, SOL_SOCKET, SO_RCVTIMEO, &opt, sizeof(int));
        if (rt)
        {
            LOG_ERROR << "setRecvTieOut error";
        }
    }
    void Socket::setRecvBuffer(const int &val)
    {
        int opt = val ? 1 : 0;
        int rt = setsockopt(m_fd, SOL_SOCKET, SO_RCVBUF, &opt, sizeof(int));
        if (rt)
        {
            LOG_ERROR << "setRecvBuffer error";
        }
    }
    void Socket::setSendBuffer(const int &val)
    {
        int opt = val ? 1 : 0;
        int rt = setsockopt(m_fd, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(int));
        if (rt)
        {
            LOG_ERROR << "setSendBuffer error";
        }
    }
    void Socket::setConnectTimeOut(const int &val)
    {
        // int rt=setsockopt(m_fd,SOL_SOCKET,SO_TI,&val,sizeof(int));
        // if (rt)
        // {
        //     LOG_ERROR << "setConnectTimeOut error";
        // }
    }

    void Socket::setTcpKeepAlive(const bool &val)
    {
        int opt = val ? 1 : 0;
        int rt = setsockopt(m_fd, SOL_SOCKET, SO_KEEPALIVE, &opt, sizeof(int));
        if (rt)
        {
            LOG_ERROR << "setTcpKeepAlive error";
        }
    }

}