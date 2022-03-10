/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-09 16:15:23
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 17:57:55
 * @Description: 
 */
#ifndef __TCPSERVER__H__
#define __TCPSERVER__H__
#include <memory>
#include <sys/types.h>
#include <stdint.h>
#include <map>
struct sockaddr_in;
namespace Itachi
{
    class EventLoop;
    class Aadaptor;
    class ThreadPool_eventLoop;
    class TcpConnection;
    class TcpServer
    {
    public:
        using MapType=std::map<std::string,std::shared_ptr<TcpConnection>>;
        TcpServer(sockaddr_in *,const std::string&name="");
        TcpServer(const char *IpV4Addr, const uint16_t &Port,const std::string&name="");
        ~TcpServer();
        void start();
        void newConnectionCallBasck(int fd,sockaddr_in*addr);
        void connection();
        void removeConnection(std::shared_ptr<TcpConnection> connection);
    private:
        std::atomic<int>m_nextId;
        bool m_isStart;
        TcpConnectionCallBack m_ConnectionCallBack;
        TcpErrorCallBack m_ErrorCallBack;
        TcpMessaageCallBack m_messageCallBack;
        std::unique_ptr<EventLoop> m_AdaptorLoop;
        std::unique_ptr<Aadaptor> m_adaptor;
        std::unique_ptr<ThreadPool_eventLoop> m_threadPool;
        MapType m_connections;
        std::string m_name;
    };
}

#endif