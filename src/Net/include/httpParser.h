/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-02-07 23:39:34
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 09:02:28
 * @Description: 
 */
#ifndef __HTTPPARSER__H__
#define __HTTPPARSER__H__
#include"httpRequest.h"
#include"httpResponse.h"
#include<memory>
#include<functional>
namespace Itachi{
    class Buffer;
namespace http{
    class HttpParser{
    public:
        enum HttpParserState{
            OK,
            FAILED,
            UNDERWAY,
            UNDERWAY_HEADERS,
        };
        HttpParser():
        m_state(UNDERWAY)
        {
        }
        bool paraerRequest(Buffer&buffer,const TimeStamp reveive_time);
        void reset(){
            m_state=UNDERWAY;
            m_request.reset();
        }
        HttpRequest* getHttpRequest(){
            return &m_request;
        }
    private:
        bool parserRequestLine(const char*start,const char*end);
        HttpParserState m_state;
        HttpRequest m_request;
    };
}
}
#endif