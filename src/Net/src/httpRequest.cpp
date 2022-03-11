/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-02-07 23:40:01
 * @LastEditors: lqf
 * @LastEditTime: 2022-02-08 20:01:43
 * @Description: 
 */
#include"httpRequest.h"
#include<string>
#include<sstream>
namespace Itachi{
namespace http{
        std::ostream & HttpRequest::dump(std::ostream&os){
            os<<HttpMethod_toString(m_method)<<" "
                <<m_path<<" "
                <<HttpVersion_toString(m_version)<<" "<<"\r\n";
            for(auto &val:m_headers){
                os<<val.first
                    <<": "
                    <<val.second
                    <<"\r\n";
            }
            if(m_query.empty()){
                return os;
            }
            os<<"\r\n"
                <<m_query;
            return os;
        }
        std::string HttpRequest::toString(){
            std::stringstream ss;
            dump(ss);
            return ss.str();
        }
}
}