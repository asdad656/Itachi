/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-09 16:15:23
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 18:41:48
 * @Description: 
 */
#ifndef __TCPSERVER__H__
#define __TCPSERVER__H__
#include <memory>
#include <sys/types.h>
#include <stdint.h>
#include<atomic>
#include <map>
struct sockaddr_in;
namespace Itachi
{
    class EventLoop;
    class Aadaptor;
    class ThreadPool_eventLoop;
    class TcpConnection;
    class TimeStamp;
    class TcpServer
    {
    public:
        using MapType=std::map<std::string,std::shared_ptr<TcpConnection>>;
        TcpServer(sockaddr_in *,const std::string&name="");
        TcpServer();
        TcpServer(const char *IpV4Addr, const uint16_t &Port,const std::string&name="");
        ~TcpServer();
        void start();
        void newConnectionCallBasck(int fd,sockaddr_in*addr);
        void connection();
        void removeConnection(std::shared_ptr<TcpConnection> connection,const TimeStamp& timeStemp);
        void setMessageCallBack(TcpMessaageCallBack cb){
            m_messageCallBack=std::move(cb);
        }
        void setErrorCallBack(TcpErrorCallBack cb){
            m_ErrorCallBack=std::move(cb);
        }
        void setConnectionCallBack(TcpConnectionCallBack cb){
            m_ConnectionCallBack=std::move(cb);
        }
        void setTcpNoDealy(bool);
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