/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-09 16:15:37
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-12 12:58:22
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
#include "timeStamp.h"
#include "config.h"
#include <string>
namespace Itachi
{
    ConfigVar<uint16_t>::ptr tcp_listenPort =
        Config::LookUp(".tcpserver.listenport", (uint16_t)5301);
    ConfigVar<std::string>::ptr tcp_serverName =
        Config::LookUp(".tcpserver.threaddefaultname", (std::string) " ");
    ConfigVar<std::string>::ptr tcp_listenaddr =
        Config::LookUp(".tcpserver.listenaddr", (std::string) "127.0.0.1");
    TcpServer::TcpServer() : m_isStart(false),
                             m_AdaptorLoop(new EventLoop()),
                             m_threadPool(new ThreadPool_eventLoop),
                             m_name(tcp_serverName->getVar()),
                             m_nextId(0)
    {
        sockaddr_in *addr = new sockaddr_in;
        bzero(addr, sizeof(sockaddr_in));
        addr->sin_family = AF_INET;
        addr->sin_port = htons(tcp_listenPort->getVar());
        inet_aton(tcp_listenaddr->getVar().c_str(), &(addr->sin_addr));
        m_adaptor.reset(new Aadaptor(m_AdaptorLoop.get(), addr));
    }

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
    {
        sockaddr_in *addr = new sockaddr_in;
        addr->sin_family = AF_INET;
        addr->sin_port = htons(Port);
        addr->sin_addr.s_addr = inet_addr(IpV4Addr);
        m_adaptor.reset(new Aadaptor(m_AdaptorLoop.get(), addr));
    }
    TcpServer ::~TcpServer()
    {
    }
    void TcpServer::start()
    {
        m_adaptor->setReadCallBack(std::bind(&TcpServer::newConnectionCallBasck, this,
                                             std::placeholders::_1, std::placeholders::_2));
        m_threadPool->start();
        m_AdaptorLoop->runInLoop(
            std::bind(&Aadaptor::listen, m_adaptor.get()));
        m_AdaptorLoop->loop();
    }
    void TcpServer::removeConnection(std::shared_ptr<TcpConnection> connection, const TimeStamp &timeStemp)
    {
        for (auto &val : m_connections)
        {
            if (val.second == connection)
            {
                m_connections.erase(val.first);
                auto loop = connection->getLoop();
                loop->queueInLoop(std::bind(
                    &TcpConnection::connectionDestory, connection));
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
        newConection->setCloseCallBack(std::bind(&TcpServer::removeConnection, this, std::placeholders::_1, std::placeholders::_2));
        newConection->setErrorCallBack(m_ErrorCallBack);
        if (m_ConnectionCallBack)
            newConection->setConnectionCallBack(m_ConnectionCallBack);
        newConection->setMessageCallBack(m_messageCallBack);
        m_connections[newConection->getName()] = newConection;
        newConection->getLoop()->queueInLoop(
            std::bind(&TcpConnection::connectionEntablish, newConection.get()));
        LOG_DEBUG << newConection->getName() << "  new connection insert m_connections!!";
    }
    void TcpServer::setTcpNoDealy(bool val)
    {
        m_adaptor->setTcpNoDealy(val);
    }

}