/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-02-08 01:25:09
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 09:41:30
 * @Description: 
 */
#include"httpParser.h"
#include"buffer.h"
#include<string>
namespace Itachi{
namespace http{

    std::string HttpVersion_toString(const HttpRequest::HttpVersion&version){
        return "HTTP/"+
                    std::to_string((version&1))+
                    "."+
                    std::to_string((version>>4)&1);
    }
    std::string HttpMethod_toString(const HttpMethod&method){
        #define HttpMethod_toString(value,name,describe)    \
                    if(method==value)   \
                    return #describe;   \

        HTTP_METHOD_MAP(HttpMethod_toString);
        #undef HttpMethod_toString
    }
        //char* totype
    HttpMethod char_to_HttpMethod(const char *start,const char*end){
        #define cmpAndReturn(value,name,describe)   \
                if(memcmp(start,#name,end-start)==0){   \
                    return (HttpMethod)value;   \
                }   \
        
        HTTP_METHOD_MAP(cmpAndReturn);
        return HttpMethod::HTTP_INVAILD_METHOD;
    }

    HttpRequest::HttpVersion char_to_HttpVersion(const char*start,const char*end){
        std::string version(start,end);
        size_t index=version.find_last_of('.');
        if(index==version.npos){
            return 0;
        }
        HttpRequest::HttpVersion _version;
        _version=((version[index-1]-48)<<4)+(version[index+1]-48);   
        return _version;
    }
    std::string char_to_HttpQuery(const char*start,const char*end){
        assert(start<=end);
        return std::string(start,end);
    }
    std::pair<std::string,std::string> char_to_HttpHeader(
        const char*start,const char*conlon,const char*end
    ) {
        assert(start<=conlon&&conlon<=end);
        const char*key_end=conlon;
        ++conlon;
        while(conlon!=end&&isspace(*conlon))++conlon;
        return std::make_pair(std::string(start,key_end),std::string(conlon,end));
    }


    bool HttpParser::paraerRequest(Buffer&buffer,const TimeStamp reveive_time){
        //  std::cout<<buffer.retrieveAllasString()<<std::endl;
        //  return true;
        bool hasmore=true;
        while(hasmore){  
            if(m_state==UNDERWAY){
                const char*crtf=buffer.findCRILF();
                if(crtf){
                    if(parserRequestLine(buffer.beginRead(),crtf)){
                        buffer.readUntil(crtf+2);
                        m_state=UNDERWAY_HEADERS;
                    }else{
                        std::cout<<"paraerRequest failed at parserRequestLine"<<std::endl;
                        //m_state=FAILED;
                        return false;
                    }
                }else{
                    m_state=FAILED;
                    return false;
                }
            }else if(m_state==UNDERWAY_HEADERS){
                const char*crtf=buffer.findCRILF();
                if(crtf==NULL){
                    m_state=OK;
                    hasmore=false;
                    continue;
                }
                const char*conlon=std::find((const char*)buffer.beginRead(),crtf,':');
                if(conlon==buffer.beginRead()){
                    buffer.readUntil(crtf+2);
                    continue;
                }
                if(conlon!=crtf){
                    m_request.addHeader((const char*)buffer.beginRead(),conlon,crtf);
                    buffer.readUntil(crtf+2);
                }else{
                    std::cout<<"paraerRequest failed at parserRequestLine"<<std::endl;
                // m_state=FAILED;
                    return false;
                }
            }else{
                return false;
            }
        }
       return true;
    }
    bool HttpParser::parserRequestLine(const char*start,const char*end){
        const char*space=std::find(start,end,' ');
        if(space!=end&&m_request.setMethod(start,space)){
            start=space+1;
            space=std::find(start,end,' ');
            if(space!=end){
                const char*question=std::find(start,space,'?');
                if(question!=space){
                    m_request.setQuery(start,space);
                    m_request.setPath(start,end);
                } else{
                    m_request.setPath(start,space);
                }
            }else{
                std::cout<<"parserRequestLine at find space "<<std::endl;
                m_state=FAILED;
                return false;
            }
            start=space+1;
            if(end-start!=8||!std::equal(start,end-1,"HTTP/1.")){
                std::cout<<"parserRequestLine at parser version "<<std::endl;          
                m_state=FAILED;
                return false;
            }else{
                m_request.setVersion(start,end);
            }
        }else{
            //error
            std::cout<<"parserRequestLine at setMethod error"<<std::endl;
            m_state=FAILED;
            return false;
        }
        return true;
    }

    void HttpRequest::addHeader(const char*start,const char*conlon,const char*end){
        std::pair<std::string,std::string> element=
            char_to_HttpHeader(start,conlon,end);
        while(!element.second.empty()&&element.second.back()==' ')
            element.second.pop_back();
        m_headers.insert(std::move(element));
    }
    void HttpRequest::setQuery(const char*start,const char*end){
        std::string query=char_to_HttpQuery(start,end);
        setQuery(query);
    }
    void HttpRequest::setPath(const char*start,const char*end){
        std::string path=char_to_HttpQuery(start,end);
        setPath(path);
    }  
    void HttpRequest::setVersion(const char*start,const char*end){
        m_version=char_to_HttpVersion(start,end);
    }
    bool HttpRequest::setMethod(const char*start,const char*end){
        return setMethod(char_to_HttpMethod(start,end));
    }
}
}