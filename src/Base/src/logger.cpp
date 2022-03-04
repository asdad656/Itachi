/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-03 17:09:30
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-04 21:44:40
 * @Description: 
 */
#include"../include/logger.h"
#include<string>
#include<sstream>
#include<memory>
#include<functional>

namespace Itachi{

    std::string LogLevel::ToString(const LogLevel::Level&level){
        #define XX(ARG,STANDERED)                   \
            if(ARG==LogLevel::STANDERED)            \
                return #STANDERED;
        XX(level,ALL);
        XX(level,DEBUG);
        XX(level,INFO);
        XX(level,WARN);
        XX(level,ERROR);            
        XX(level,FATAL);            
        XX(level,OFF);
        XX(LogLevel::WRONGLEVEL,WRONGLEVEL);
        #undef XX
    }

    LogLevel::Level LogLevel::FromString(const std::string&level){
         #define XX(STANDARD)                               \
            if(#STANDARD==level)                              \
                return LogLevel::STANDARD;              \

        XX(ALL)
        XX(DEBUG)
        XX(INFO)
        XX(WARN)
        XX(ERROR)       
        XX(FATAL)       
        XX(OFF)
        return LogLevel::WRONGLEVEL;
     }


class  LogLevelFormater: public LogFormatter::LogItemFormatter{
public:
    LogLevelFormater(const std::string&conditionOrformat):
    LogItemFormatter(conditionOrformat)
    {
    }
    /**
     * @description:                                    输出日志的级别
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */    
    void operator()(const LogMessage&logMessage,std::ostream&os)const override{
        os<<LogLevel::ToString(logMessage.getLevel());
    } 
private:
};


class  LogMessageFormatter: public LogFormatter::LogItemFormatter{
public:

    LogMessageFormatter(const std::string&conditionOrformat):
    LogItemFormatter(conditionOrformat)
    {
    }
    /**
     * @description:                                    输出日志的消息体
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */    
    void operator()(const LogMessage&logMessage,std::ostream&os)const override{
        os<<logMessage.getMessageStream();
    } 
private:
};


class  LogTimeFormatter: public LogFormatter::LogItemFormatter{
public:
    LogTimeFormatter(const std::string&conditionOrformat="%Y-%m-%d %H:%M:%S"):
    LogItemFormatter(conditionOrformat)
    {
    }
    /**
     * @description:                                    输出日志的日期
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */    
    void operator()(const LogMessage&logMessage,std::ostream&os)const override{
        const  time_t &time=logMessage.getTime();
        struct tm time_formater;
        localtime_r(&time,&time_formater);
        char timeformatter[48];
        strftime(timeformatter,sizeof(timeformatter),m_conditionOrformat.c_str(),&time_formater);
        os<<timeformatter;
    }
}; 

class  LogCharacterFormatter: public LogFormatter::LogItemFormatter{
public:
    LogCharacterFormatter(const std::string&conditionOrformat):
    LogItemFormatter(conditionOrformat)
    {
    }
    /**
     * @description:                                    输出日志的年份
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */    
    void operator()(const LogMessage&logMessage,std::ostream&os)const override{
        os<<m_conditionOrformat;
    } 
private:
};

class  LogNewLineFormatter: public LogFormatter::LogItemFormatter{
public:
    LogNewLineFormatter()
    {
    }
    /**
     * @description:                                    输出日志的年份
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */    
    void operator()(const LogMessage&logMessage,std::ostream&os)const override{
        os<<std::endl;
    } 
private:
};

    //%m 消息体
    //%p  level
    //%r   启动后的时间
    //%c   分割符号
    //%t    县城id
    //%n   回车
    //%d   时间戳
    //%f    文件名
    //%l    行号
    //%N 线程name

void LogFormatter::init(){
    size_t right=0;
    size_t left=0;
    size_t length=m_formatter.size();
    std::string itemFormatter="";
    while(right<length||left<length){
        while(right<length&&m_formatter[right]!='%'){
            ++right;
        }

        if(m_formatter[left]!='%')
        {
             itemFormatter=m_formatter.substr(left,right-left);
             left=right++;
        }
        else
        {
             itemFormatter=m_formatter.substr(left,2);
             left+=2;
        }
        
        #define XX(PATTERN,FORMATER_CLASS)                                   \
            if(itemFormatter==#PATTERN||#PATTERN=="%c") {                 \
            addItemFormatter(new FORMATER_CLASS(itemFormatter));      \
            continue;                                                                               \
            }                                                                                            \

        XX(%m,LogMessageFormatter)
        XX(%p,LogLevelFormater)
        XX(%t,LogMessageFormatter)
        XX(%d,LogTimeFormatter)
        XX(%c,LogCharacterFormatter)
        #undef XX
        addItemFormatter(new LogNewLineFormatter);
    }
}

//-------------------------------LogManager-----------------------------//
LogManager::MapType LogManager::m_appenders;
}