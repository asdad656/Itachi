/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-02-07 23:40:10
 * @LastEditors: lqf
 * @LastEditTime: 2022-02-09 13:14:25
 * @Description: 
 */
#include"httpResponse.h"
#include"httpRequest.h"
#include<sstream>
namespace Itachi{
namespace http{
    
    std::string HttpStasus_to_String(const HttpStatus status){
        #define HTTP_STATUS_TOSTRING_DEFINER(value,name,describe)   \
            if((int)status==value){                                                                      \
                return #name;                                                                       \
            }
        HTTP_STATUS_MAP(HTTP_STATUS_TOSTRING_DEFINER);
        return "HTTP_INVAILD_STATUS";
    }


    std::string HttpHeaders_to_String(const HttpResponse::MapType&headers){
        std::stringstream ss;
        for(const auto &val:headers){
            ss<<val.first
                <<": "
                <<val.second
                <<"\r\n";
        }
        ss<<"\r\n";
        return ss.str();
    }


    std::ostream&HttpResponse::dump(std::ostream&os){
        //响应行
        os<<HttpVersion_toString(m_version)
            <<" "<<m_status
            <<" "<<HttpStasus_to_String(m_status)
            <<"\r\n";
        //响应头
        os<<HttpHeaders_to_String(m_headers);
        //响应体
        os<<m_body;
        return os;
    }

    std::string HttpResponse::toString(){
        std::stringstream ss;
        dump(ss);
        return ss.str();
    }
}
}