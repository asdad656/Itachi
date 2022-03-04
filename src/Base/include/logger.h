/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-03 17:09:22
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-05 00:50:35
 * @Description: 
 */
#ifndef  __LOGGER__H_
#define __LOGGER__H_
#include<string>
#include<sstream>
#include<memory>
#include<functional>
#include<iostream>
#include<time.h>
#include<stdio.h>
#include<fstream>
#include<map>
#include<list>
#include<json.hpp>
namespace Itachi{
    struct LogLevel{
        enum Level{
            ALL,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
            OFF,
            WRONGLEVEL
        };
        static std::string ToString(const LogLevel::Level&level);
        static Level FromString(const std::string&level);
    };

    
    
    class LogMessage{
    public:
        LogMessage(const LogLevel::Level&level,
                            const char*file,
                            const char*line):
        m_level(level),
        m_file(__FILE__),
        m_line(__LINE__),
        m_time(time(NULL))
        {
            
        }
        //-----------------------------------getMethod---------------------------------------//
        inline  std::ostream&getMessageStream(){  return m_message;}
        inline const std::ostream&getMessageStream()const{  return m_message;}
        const LogLevel::Level& getLevel()const{return m_level;}
        const std::string& getFile()const{return m_file;}
        const int&getLine()const{return m_line;}
        const std::string&getThreadName()const{return m_threadName;}
        const uint64_t& getThreadId()const{return m_threadId;}
        const uint64_t&getFiberId()const{return m_fiberId;}
        const time_t&getTime()const{return m_time;}
        std::ostream&operator<<(const std::string&message){
            m_message<<message;
            return m_message;
        }

        std::ostream& dump(std::ostream&os)const {
            os<<LogLevel::ToString(m_level)<<" "
                <<m_message<<" "
                <<m_time<<" "
                <<m_file<<" "
                <<m_line<<" "
                <<m_threadId<<" "
                <<m_threadName<<" "
                <<m_fiberId<<std::endl;
        }

        std::string ToString()const{
            std::stringstream ss;
            dump(ss);
            return ss.str();
        }
        //----------------------------------setMethod---------------------------------------//
        // void  setLevel(const LogLevel::Level &level){ m_level=level;}
        // void 4_t& getThreadId(){return m_threadId;}
        // void 4_t&getFiberId(){return m_fiberId;}
     private:
        //日志级别
        LogLevel::Level m_level;
        //日志内容
        std::ostringstream m_message;
        //所处时间
        time_t m_time;
        //所在文件
        const char* m_file;
        //行号
        int m_line;
        //线程id
        uint64_t m_threadId;
        //协程id
        uint64_t m_fiberId;
        //线程名字
        std::string m_threadName;
    };


class LogFormatter{
public:
        /**
     * @description: 内部类
     * @param {*}
     * @return {*}
     */    
        LogFormatter(const std::string&formatter ):
        m_formatter(formatter){
            init();
        }
        void init();
    class LogItemFormatter{
        public:
            typedef std::shared_ptr<LogItemFormatter> ptr;
            LogItemFormatter(const std::string& conditionOrformat=""):
            m_conditionOrformat(conditionOrformat)
            {
            }
            virtual ~LogItemFormatter()
            {
                
            }
            virtual void operator()(const LogMessage&logMessage,std::ostream&os)const=0;
            
        protected:
            std::string m_conditionOrformat;
    };

    typedef std::list<LogItemFormatter::ptr>    ListType;

    inline  void addItemFormatter(LogItemFormatter*itemFormatter){
        m_logItemFormaters.push_back(std::shared_ptr<LogItemFormatter>(itemFormatter));
    }
    
    void clearItemFormatter(LogItemFormatter*itemFormatter){
        m_logItemFormaters.clear();
    }

    void format(const LogMessage&logMessage,std::ostream&os)const{
        for(const auto&val:m_logItemFormaters){
            (*val)(logMessage,os);
        }
    }
private:
    std::string m_formatter;
    ListType m_logItemFormaters;
};

//-------------loggerAppender-------------------------//
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender>      ptr;

    LogAppender(const std::string&formatter,const std::string&name=""):
    m_formatter(formatter),
    m_name(name){

    }
    virtual ~LogAppender(){

    }

    virtual std::ostream& log(const LogMessage&logMessage){
        std::ostringstream oss;
        m_formatter.format(logMessage,oss);
        std::cout<<oss.str();
    }
protected:
    LogLevel::Level m_level;
    LogFormatter m_formatter;
    std::string m_name;
};


class StdOutAppender:public LogAppender{
public:
    
private:
    
};

class FileStreamAppender : public LogAppender{
public:
    FileStreamAppender(const std::string&formatter,const std::string&name="",const std::string&fileName=""):
    LogAppender(formatter,name),
    m_fileName(fileName){
        m_fstream.open(m_fileName);
        if(!m_fstream.is_open()){
            std::cout<<"file stream open faild"<<std::endl;
        }
    }

    ~FileStreamAppender(){
        m_fstream.close();
    }
    std::ostream& log(const LogMessage&logMessage)override{
        m_formatter.format(logMessage,m_fstream);
    }
    void reopen(){
        m_fstream.close();
        m_fstream.open(m_fileName);
    }
    
private:
    std::string m_fileName;
    std::ofstream m_fstream;
};

class LogAppenderDefiner{
public:
    LogAppenderDefiner():
    m_name(""),
    m_type("stdstreasm"),
    m_filePath(""),
    m_level("DEBUG")
    {

    }
    bool operator==(const LogAppenderDefiner&b)const{
        return m_name==b.m_name&&
                m_type==b.m_type&&
                m_filePath==b.m_filePath&&
                m_level==b.m_level;
    }

    bool operator>(const LogAppenderDefiner&b)const{
        return m_name>b.m_name&&
                m_type>b.m_type&&
                m_filePath>b.m_filePath&&
                m_level>b.m_level;
    }

    bool operator<(const LogAppenderDefiner&b){
        return m_name<b.m_name&&
                m_type<b.m_type&&
                m_filePath<b.m_filePath&&
                m_level<b.m_level;
    }
    void setName(const std::string&value){m_name=value;}
    void setType(const std::string&value){m_type=value;}
    void setFilePath(const std::string&value){m_filePath=value;}
    void setLevel(const std::string&value){m_level=value;}
    void FromString(const std::string&From){
        std::string From_lowerCase(From);
        std::transform(From.begin(),From.end(),From_lowerCase.begin(),::tolower);
        nlohmann::json from=nlohmann::json::parse(From_lowerCase);
        if(!from["name"].is_null())
            from.at("name").get_to(m_name);
        if(!from["type"].is_null())
            from.at("type").get_to(m_type);
        if(!from["filepath"].is_null())
             from.at("filepath").get_to(m_filePath);
        if(!from["level"].is_null())
            from.at("level").get_to(m_level);
        if(!from["formate"].is_null())
            from.at("formate").get_to(m_formate);   
    }

    std::string ToString()const{
        std::ostringstream oss;
        oss<<"{"
             <<"name: "<<m_name<<" "
             <<"type: "<<m_type<<" "
             <<"filepath: "<<m_filePath<<" "
             <<"level: "<<m_level<<" "
             <<"formate: "<<m_formate
             <<"}";
        return oss.str();
    }
private:
    std::string m_name;
    std::string m_type;
    std::string m_filePath;
    std::string m_level;
    std::string m_formate;
};

class LogManager{
public:
    typedef  std::map<std::string,LogAppender> MapType; 
    LogManager(const LogManager&)=delete;
    LogManager&operator=(const LogManager&)=delete;
private:
    static void init();
    static LogManager&getInstance(){
        static LogManager logManager;
        return logManager;
    }
    LogManager(){
        
    }

    ~LogManager(){
        
    }
private:
    static MapType m_appenders;
};


}






#endif