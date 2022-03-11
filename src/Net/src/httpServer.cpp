/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-02-08 05:59:53
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 21:26:02
 * @Description: 
 */
#include "httpServer.h"
#include "httpResponse.h"
#include "httpParser.h"
#include "config.h"
#include <netinet/in.h>
#include <arpa/inet.h>
namespace Itachi
{

 ConfigVar<uint16_t>::ptr http_listenPort =
        Config::LookUp(".httpserver.listenport", (uint16_t)5300);
     ConfigVar<std::string>::ptr http_serverName =
        Config::LookUp("httpserver.threaddefaultname", (std::string) "");
 ConfigVar<std::string>::ptr http_listenaddr =
        Config::LookUp(".httpserver.listenaddr", (std::string) "127.0.0.1");
    namespace http
    {
        HttpServer::HttpServer() : m_name("Http Server " + http_serverName->getVar()) //+ http_serverName->getVar())
        {
            m_tcpServer.reset(new TcpServer(http_listenaddr->getVar().c_str(),http_listenPort->getVar(),m_name+"m_tcpServer"));
            m_dispatch.reset(new ServlerDispatch());
            m_tcpServer->setConnectionCallBack(
                std::bind(
                    &HttpServer::onConntction, this, std::placeholders::_1));
            m_tcpServer->setMessageCallBack(
                std::bind(
                    &HttpServer::messageCallBack,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3));
        }
        void HttpServer::onConntction(std::shared_ptr<TcpConnection> ptr)
        {
            std::stringstream ss;
            ss << "HTTP/1.1 200 OK"
               << "\r\n"
               << "Content-Type: text/html"
               << "\r\n"
               << "connection: keep-alive"
               << "\r\n"
               << "Accept-Language: zh-cn,zh;q=0.5"
               << "\r\n"
               << "Server: Itachi1.1"
               << "\r\n"
               << "content-length: 65"
               << "\r\n"
               << "\r\n"
               << "<html><head></head><body>welcome to Server_Itachi!!</body></html>";
            ptr->send(
                ss.str());
        }
        void HttpServer::messageCallBack(const std::shared_ptr<TcpConnection> &ptr, Buffer *buffer, TimeStamp receive_time)
        {
            HttpParser *parser = ptr->getHttpParser();
            if (parser == nullptr)
            {
                ptr->setHttpParser(new HttpParser);
                ptr->setTcpNoDealy(true);
                parser = ptr->getHttpParser();
            }
            if (!parser->paraerRequest(*buffer, receive_time))
            {
                std::cout << "parser error" << std::endl;
                return;
            }
            else
            {
                std::cout << std::endl
                          << parser->getHttpRequest()->toString() << std::endl;
            }

            std::unique_ptr<HttpResponse> response(new HttpResponse());
            if ("/" != parser->getHttpRequest()->getPath() && parser->getHttpRequest()->getPath() != "/favicon.ico")
            {
                LOG_DEBUG << "parser->getHttpRequest()->getPath()  :" << parser->getHttpRequest()->getPath();
                m_dispatch->handle(parser->getHttpRequest()->getPath(), *parser->getHttpRequest(), *response);
                ptr->send(
                    response->toString());
            }
            else
            {
                onConntction(ptr);
            }
            parser->reset();
        }
        void HttpServer::addServlet(const std::string &key, Servlet *servlet)
        {
            m_dispatch->addServlet(key, servlet);
        }
        void HttpServer::addServlet(const std::string &key, Servlet::CallBack cb)
        {
            m_dispatch->addServlet(key, cb);
        }
        void HttpServer::delServlet(const std::string &key)
        {
            m_dispatch->delServlet(key);
        }
    }
}