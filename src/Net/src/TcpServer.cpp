/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-09 16:15:37
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 18:46:08
 * @Description: 
 */
#include "EventLoop.h"
#include "adaptor.h"
#include <map>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "threadpool_c++11.h"
#include "definition.h"
#include "Tcpserver.h"
#include "tcpConnection.h"
namespace Itachi
{
    TcpServer::TcpServer(sockaddr_in *addr, const std::string &name) : m_isStart(false),
                                                                       m_AdaptorLoop(new EventLoop()),
                                                                       m_adaptor(new Aadaptor(m_AdaptorLoop.get(), addr)),
                                                                       m_threadPool(new ThreadPool_eventLoop),
                                                                       m_name(name),
                                                                       m_nextId(0)
    {
    }
    TcpServer::TcpServer(const char *IpV4Addr, const uint16_t &Port, const std::string &name) : m_isStart(false),
                                                                                                m_AdaptorLoop(new EventLoop()),
                                                                                                m_threadPool(new ThreadPool_eventLoop),
                                                                                                m_name(name),
                                                                                                m_nextId(0)
    //m_adaptor(new Aadaptor(m_AdaptorLoop.get()))
    {
        sockaddr_in *addr = new sockaddr_in;
        addr->sin_family = AF_INET;
        addr->sin_port = htons(Port);
        addr->sin_addr.s_addr = inet_addr(IpV4Addr);
        m_adaptor.reset(new Aadaptor(m_AdaptorLoop.get(), addr));
    }
    TcpServer ::~TcpServer(){


    }
    void TcpServer::start()
    {
        m_adaptor->setReadCallBack(std::bind(&TcpServer::newConnectionCallBasck, this,
                                             std::placeholders::_1, std::placeholders::_2));
        m_AdaptorLoop->runInLoop(
            std::bind(&Aadaptor::listen, m_adaptor.get()));
        m_threadPool->start();
        m_AdaptorLoop->loop();
    }
    void TcpServer::removeConnection(std::shared_ptr<TcpConnection> connection)
    {
        for (auto &val : m_connections)
        {
            if (val.second == connection)
            {
                m_connections.erase(val.first);
                auto loop=connection->getLoop();
                loop->queueInLoop(std::bind(
                    &TcpConnection::connectionDestory,connection
                ));
                return;
            }
        }
        LOG_FATAL << "removeConnection failed";
    }
    void TcpServer::newConnectionCallBasck(int fd, sockaddr_in *addr)
    {
        auto loop = m_threadPool->getALoop();
        std::shared_ptr<TcpConnection> newConection(new TcpConnection(loop,
                                                                      fd,
                                                                      addr,
                                                                      m_adaptor->getLocalAddr(),
                                                                      m_name + std::to_string(++m_nextId)));
        newConection->setCloseCallBack(std::bind(&TcpServer::removeConnection,this,std::placeholders::_1));
        newConection->setErrorCallBack(m_ErrorCallBack);
        newConection->setConnectionCallBack(m_ConnectionCallBack);
        newConection->setMessageCallBack(m_messageCallBack);
        m_connections[newConection->getName()] = newConection;
        LOG_DEBUG <<newConection->getName()<< "  new connection insert m_connections!!";
    }
}