/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-02-08 23:06:31
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 10:51:58
 * @Description: 
 */
#ifndef __HTTP__SERVLET__H__
#define __HTTP__SERVLET__H__
#include <memory>
#include <functional>
#include <string>
#include <fstream>
#include <map>
#include "httpResponse.h"
#include "httpRequest.h"
namespace Itachi
{
    namespace http
    {
        class ServlerDispatch;
        class Servlet;
        static thread_local ServlerDispatch *thread_DisPatch = nullptr;

        class Servlet
        {
        public:
            typedef std::function<void(HttpRequest &request, HttpResponse &response)> CallBack;
            Servlet(CallBack cb) : m_cb(std::move(cb))
            {
            }
            Servlet() {}
            virtual ~Servlet();
            virtual void handle(HttpRequest &request, HttpResponse &response);

        protected:
            CallBack m_cb;
            //std::string m_name;
        };

        class NotFoundServlet : public Servlet
        {
        public:
            NotFoundServlet() : Servlet()
            {
            }
            ~NotFoundServlet();
            void handle(HttpRequest &request, HttpResponse &response) override;
        };

        class FileServlet : public Servlet
        {
        public:
            FileServlet(CallBack cb) : Servlet(cb)
            {
            }
            FileServlet()
            {
            }
            void handle(HttpRequest &request, HttpResponse &response) override;

        private:
            std::fstream m_fileStream;
        };

        class ServlerDispatch
        {
        public:
            ServlerDispatch()
            {
                m_servlets["notFound"] = std::make_shared<NotFoundServlet>();
                m_servlets["FileSetvlet"] = std::make_shared<FileServlet>();
            };
            void addServlet(const std::string &key, Servlet *servlet);
            void addServlet(const std::string &key, Servlet::CallBack cb);
            void delServlet(const std::string &key);
            std::shared_ptr<Servlet> getServlet(const std::string &key);
            void handle(const std::string &key, HttpRequest &request, HttpResponse &response)
            {
                // auto it = m_servlets.find(key);
                // if (it != m_servlets.end())
                if(m_servlets["FileSetvlet"] !=nullptr)
                {
                  m_servlets["FileSetvlet"]->handle(request, response);
                }
                else
                {
                    m_servlets["notFound"]->handle(request, response);
                }
            }

        private:
            std::map<std::string, std::shared_ptr<Servlet>> m_servlets;
        };
    }
}

#endif