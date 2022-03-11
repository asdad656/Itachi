/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-02-07 23:39:27
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 09:01:57
 * @Description: 
 */
#ifndef __HTTPREQUEST__H__
#define __HTTPREQUEST__H__
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include"timeStamp.h"
#include<boost/lexical_cast.hpp>
namespace Itachi{
namespace http{
    class HttpRequest;
    //httpmethod
#define HTTP_METHOD_MAP(XX)         \
    XX(0,  DELETE,      DELETE)       \
    XX(1,  GET,         GET)          \
    XX(2,  HEAD,        HEAD)         \
    XX(3,  POST,        POST)         \
    XX(4,  PUT,         PUT)          \
    /* pathological */                \
    XX(5,  CONNECT,     CONNECT)      \
    XX(6,  OPTIONS,     OPTIONS)      \
    XX(7,  TRACE,       TRACE)        \
    /* WebDAV */                      \
    XX(8,  COPY,        COPY)         \
    XX(9,  LOCK,        LOCK)         \
    XX(10, MKCOL,       MKCOL)        \
    XX(11, MOVE,        MOVE)         \
    XX(12, PROPFIND,    PROPFIND)     \
    XX(13, PROPPATCH,   PROPPATCH)    \
    XX(14, SEARCH,      SEARCH)       \
    XX(15, UNLOCK,      UNLOCK)       \
    XX(16, BIND,        BIND)         \
    XX(17, REBIND,      REBIND)       \
    XX(18, UNBIND,      UNBIND)       \
    XX(19, ACL,         ACL)          \
    /* subversion */                  \
    XX(20, REPORT,      REPORT)       \
    XX(21, MKACTIVITY,  MKACTIVITY)   \
    XX(22, CHECKOUT,    CHECKOUT)     \
    XX(23, MERGE,       MERGE)        \
    /* upnp */                        \
    XX(24, MSEARCH,     M-SEARCH)     \
    XX(25, NOTIFY,      NOTIFY)       \
    XX(26, SUBSCRIBE,   SUBSCRIBE)    \
    XX(27, UNSUBSCRIBE, UNSUBSCRIBE)  \
    /* RFC-5789 */                    \
    XX(28, PATCH,       PATCH)        \
    XX(29, PURGE,       PURGE)        \
    /* CalDAV */                      \
    XX(30, MKCALENDAR,  MKCALENDAR)   \
    /* RFC-2068, section 19.6.1.2 */  \
    XX(31, LINK,        LINK)         \
    XX(32, UNLINK,      UNLINK)       \
    /* icecast */                     \
    XX(33, SOURCE,      SOURCE)       
    
    enum HttpMethod{
        #define HttpMethod(value,name,describe) name=value,
        HTTP_METHOD_MAP(HttpMethod)
        #undef HttpMethod
        HTTP_INVAILD_METHOD,
    };

    class HttpRequest{
    public:
        typedef std::map<std::string,std::string> MapType;
        typedef int8_t HttpVersion;

        std::ostream & dump(std::ostream&os);
        std::string toString();

        //**************************getMethod******************//
        HttpMethod getMethod()const{return m_method;}
        HttpVersion getVersion()const{return m_version;}
        const std::string&getPath()const{return m_path;}
        const std::string&getQuery()const{return m_query;}
        const MapType&getHeaders()const{return m_headers;}
        const TimeStamp&getReceiveTIme()const{return m_receiveTime;}
        template<class T>
        T getHeaderAs(const std::string & key,T&defaultVal){
            auto it=m_headers.find(key);
            if(it==m_headers.end()){
                return defaultVal;
            }
            try{
                T val=boost::lexical_cast<T>(it->second);
                return val;       
            } catch(...){
                //error log
            }         
            return defaultVal;
        }
        //**************************setMethod****************//
        bool setMethod(HttpMethod method){
            m_method=method;
            return method!=HTTP_INVAILD_METHOD;
        }
        bool setMethod(const char*start,const char*end);
        void serVersion(HttpVersion version){m_version=version;}
        void setVersion(const char*start,const char*end);
        void setPath(const std::string &path){m_path=path;}
        void setPath(const char*start,const char*end);
        void setQuery(const std::string&query){m_query=query;}
        void setQuery(const char*start,const char*end);

        void serReveiveTime(TimeStamp reveiveme){m_receiveTime=reveiveme;}
        // template<class T>
        // void addHeader(const std::string&key,const T&val){
        //     try
        //     {
        //         std::string val=std::to_string(val);
        //         m_headers[key]=val;
        //     }
        //     catch(...)
        //     {
        //         //error log
        //     }
        // }

        void addHeader(const std::string&key,const std::string&value){
            m_headers[key]=value;
        }
        void addHeader(const char*start,const char*conlon,const char*end);

        void swap(HttpRequest &s){
            m_path.swap(s.m_path);
            m_headers.swap(m_headers);
            m_query.swap(s.m_query);
            m_receiveTime.swap(s.m_receiveTime);
            std::swap(m_method,s.m_method);
            std::swap(m_version,s.m_version);
        }

        void reset(){
            m_path.clear();
            m_headers.clear();
            m_query.clear();
            m_method=HTTP_INVAILD_METHOD;
            m_version=0;
        }
    private:
        //请求方式
        HttpMethod m_method;
        //请求版本
        HttpVersion m_version;
        //请求 资源
        std::string m_path;
        //请求头
        MapType m_headers;
        //请求体
        std::string m_query;
        //超时时间
        TimeStamp m_receiveTime;
    };
    //to_string method
    std::string HttpVersion_toString(const HttpRequest::HttpVersion&version);
    std::string HttpMethod_toString(const HttpMethod&method);
        //char* totype
    HttpMethod char_to_HttpMethod(const char *start,const char*end);
    HttpRequest::HttpVersion char_to_HttpVersion(const char*start,const char*end);
    std::string char_to_HttpQuery(const char*start,const char*end);
    std::pair<std::string,std::string> char_to_HttpHeader(
        const char*start,const char*conlon,const char*end
    ) ;
}
}
#endif