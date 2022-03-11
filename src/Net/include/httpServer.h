/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-02-08 05:59:59
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 21:00:05
 * @Description: 
 */
#ifndef __HTTPDERVER__H__
#define __HTTPDERVER__H__
#include <tcpConnection.h>
#include "Tcpserver.h"
#include "buffer.h"
#include "callback.h"
#include "httpServlet.h"
#include <functional>
#include <memory>
struct sockaddr_in;
// using namespace Itachi::net;
namespace Itachi
{
    class EventLoop;
    namespace http
    {
        class HttpServer
        {
        public:
            typedef std::shared_ptr<HttpServer> ptr;
            // HttpServer(EventLoop*work_loop,sockaddr_in* work_addr, const std::string& name=""):
            HttpServer();
            HttpServer(sockaddr_in *work_addr, const std::string &name = "") : m_tcpServer(new TcpServer(work_addr, "TcpServer under HttpServer" + name)),
                                                                               m_name("Http Server " + name)
            {
                m_dispatch.reset(new ServlerDispatch());
                // m_tcpServer->setConnectionCallBack(
                //     std::bind(
                //         &HttpServer::onConntction, this, std::placeholders::_1));
                m_tcpServer->setMessageCallBack(
                    std::bind(
                        &HttpServer::messageCallBack,
                        this,
                        std::placeholders::_1,
                        std::placeholders::_2,
                        std::placeholders::_3));
            }

            void messageCallBack(const std::shared_ptr<TcpConnection> &, Buffer *, TimeStamp);
            void onConntction(std::shared_ptr<TcpConnection> ptr);
            void start()
            {
                m_tcpServer->start();
            }
            void addServlet(const std::string &key, Servlet *servlet);
            void addServlet(const std::string &key, Servlet::CallBack cb);
            void delServlet(const std::string &key);

        private:
            std::unique_ptr<TcpServer> m_tcpServer;
            std::string m_name;
            std::shared_ptr<ServlerDispatch> m_dispatch;
        };
    }
}

#endif
