/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-02-08 23:06:38
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 10:52:36
 * @Description: 
 */
#include "httpServlet.h"
#include "httpResponse.h"
#include "httpRequest.h"
namespace Itachi
{
    namespace http
    {
        void Servlet::handle(HttpRequest &request, HttpResponse &response)
        {
            if (m_cb)
            {
                m_cb(request, response);
            }
        }
        Servlet::~Servlet()
        {
        }
        void ServlerDispatch::addServlet(const std::string &key, Servlet *servlet)
        {
            m_servlets[key] = std::make_shared<Servlet>(*servlet);
        }

        void ServlerDispatch::addServlet(const std::string &key, Servlet::CallBack cb)
        {
            m_servlets[key] = std::make_shared<Servlet>(cb);
        }

        void ServlerDispatch::delServlet(const std::string &key)
        {
            auto it = m_servlets.find(key);
            if (it != m_servlets.end())
            {
                m_servlets.erase(it);
            }
        }

        std::shared_ptr<Servlet> ServlerDispatch::getServlet(const std::string &key)
        {
            auto it = m_servlets.find(key);
            return it == m_servlets.end() ? nullptr : it->second;
        }

        NotFoundServlet::~NotFoundServlet()
        {
        }
        void NotFoundServlet::handle(HttpRequest &request, HttpResponse &response)
        {
            response.setVersion(request.getVersion());
            response.setStatus(HttpStatus::NOT_FOUND);
            response.addHeader("Content-Type", "text/html;charset=UTF-8");
            response.addHeader("Accept-Language", "zh-cn,zh;q=0.5");
            response.addHeader("connection", "keep-alive");
            std::string body = "你访问的页面不见拉";
            response.addHeader("content-length", body.size());
            response.setBody(body);

            // response.setVersion(request.getVersion());
            // response.setStatus(HttpStatus::OK);
            // response.addHeader("connection","keep-alive");
            // std::string body;
            // std::ifstream fs;
            // std::string filePath="home/abc/src"+request.getPath().substr(request.getPath().find_last_of('/'));
            // fs.open(filePath,std::ios::binary);
            // if(fs.is_open()){
            //     response.addHeader( "content-disposition","attachment;"+request.getPath().substr(request.getPath().find_last_of('/')));
            //     std::stringstream ss;
            //     ss<<fs.rdbuf();
            //     body=ss.str();
            // }
            // response.addHeader("content-length",body.size());
            // response.setBody(body);
        }

        void FileServlet::handle(HttpRequest &request, HttpResponse &response)
        {

            std::string body;
            std::ifstream fs;
            std::string filePath = "home/abc/src" + request.getPath().substr(request.getPath().find_last_of('/'));
            fs.open(filePath, std::ios::binary);
            if (fs.is_open())
            {
                response.addHeader("content-disposition", "attachment;" + request.getPath().substr(request.getPath().find_last_of('/')));
                std::stringstream ss;
                ss << fs.rdbuf();
                body = ss.str();
            }else{
                response.setVersion(request.getVersion());
                response.setStatus(HttpStatus::NOT_FOUND);
                response.addHeader("Content-Type", "text/html;charset=UTF-8");
                response.addHeader("Accept-Language", "zh-cn,zh;q=0.5");
                response.addHeader("connection", "keep-alive");
                std::string body = "你访问的页面不见拉";
                response.addHeader("content-length", body.size());
                response.setBody(body);
                return;
            }
            response.setVersion(request.getVersion());
            response.setStatus(HttpStatus::OK);
            response.addHeader("connection", "keep-alive");
            response.addHeader("content-length", body.size());
            response.setBody(body);
        }
    }
}