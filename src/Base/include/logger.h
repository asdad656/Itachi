/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-03 17:09:22
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-06 12:50:34
 * @Description: 
 */
#ifndef __LOGGER__H_
#define __LOGGER__H_
#include <string>
#include <sstream>
#include <memory>
#include <functional>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <fstream>
#include <map>
#include <list>
#include <json.hpp>
#include <thread>
#include "threadpool_c++11.h"

namespace Itachi
{
    struct LogLevel
    {
        enum Level
        {
            ALL,
            DEBUG,
            INFO,
            WARN,
            ERROR,
            FATAL,
            OFF,
            WRONGLEVEL
        };
        static std::string ToString(const LogLevel::Level &level);
        static Level FromString(const std::string &level);
    };

    class LogMessage
    {
    public:
        LogMessage(const LogLevel::Level &level,
                   const char *file,
                   int line) : m_level(level),
                               m_file(file),
                               m_line(line),
                               m_time(time(NULL)),
                               m_threadId(getCurrentThreadId()),
                               m_threadName(getCurrentThreadName())
        {
        }
        //-----------------------------------getMethod---------------------------------------//
        inline std::ostream &getMessageStream() { return m_message; }
        inline const std::ostream &getMessageStream() const { return m_message; }
        const std::string getMessage() const { return m_message.str(); }
        const LogLevel::Level &getLevel() const { return m_level; }
        const char *getFile() const { return m_file; }
        const int &getLine() const { return m_line; }
        const std::string &getThreadName() const { return m_threadName; }
        const std::thread::id &getThreadId() const { return m_threadId; }
        const uint64_t &getFiberId() const { return m_fiberId; }
        const time_t &getTime() const { return m_time; }
        void operator<<(const std::string &message)
        {
            m_message << message;
        }

        std::ostream &dump(std::ostream &os) const
        {
            os << LogLevel::ToString(m_level) << " "
               << m_message << " "
               << m_time << " "
               << m_file << " "
               << m_line << " "
               << m_threadId << " "
               << m_threadName << " "
               << m_fiberId << std::endl;
            return os;
        }

        std::string ToString() const
        {
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
        const char *m_file;
        //行号
        int m_line;
        //线程id
        std::thread::id m_threadId;
        //协程id
        uint64_t m_fiberId;
        //线程名字
        std::string m_threadName;
    };

    class LogFormatter
    {
    public:
        /**
     * @description: 内部类
     * @param {*}
     * @return {*}
     */
        LogFormatter(const std::string &formatter) : m_formatter(formatter)
        {
            init();
        }
        void init();
        class LogItemFormatter
        {
        public:
            typedef std::shared_ptr<LogItemFormatter> ptr;
            LogItemFormatter(const std::string &conditionOrformat = "") : m_conditionOrformat(conditionOrformat)
            {
            }
            virtual ~LogItemFormatter()
            {
            }
            virtual void operator()(const LogMessage &logMessage, std::ostream &os) const = 0;

        protected:
            std::string m_conditionOrformat;
        };

        typedef std::list<LogItemFormatter::ptr> ListType;

        inline void addItemFormatter(LogItemFormatter *itemFormatter)
        {
            m_logItemFormaters.push_back(std::shared_ptr<LogItemFormatter>(itemFormatter));
        }

        void clearItemFormatter(LogItemFormatter *itemFormatter)
        {
            m_logItemFormaters.clear();
        }

        void format(const LogMessage &logMessage, std::ostream &os) const
        {
            for (const auto &val : m_logItemFormaters)
            {
                (*val)(logMessage, os);
            }
        }

    private:
        std::string m_formatter;
        ListType m_logItemFormaters;
    };

    //-------------loggerAppender-------------------------//
    class LogAppender
    {
    public:
        typedef std::shared_ptr<LogAppender> ptr;

        LogAppender(const std::string &formatter, const std::string &name = "") : m_formatter(formatter),
                                                                                  m_name(name)
        {
        }
        virtual ~LogAppender()
        {
        }

        const std::string &getName() const
        {
            return m_name;
        }

        const LogLevel::Level &getLevel() const
        {
            return m_level;
        }

        void setName(const std::string &name)
        {
            m_name = name;
        }

        void setLevel(const LogLevel::Level &level)
        {
            m_level = level;
        }

        virtual void log(const LogMessage &logMessage)
        {
            std::ostringstream oss;
            m_formatter.format(logMessage, oss);
            std::cout << oss.str();
        }

    protected:
        LogLevel::Level m_level;
        LogFormatter m_formatter;
        std::string m_name;
    };

    class StdOutAppender : public LogAppender
    {
    public:
        StdOutAppender(const std::string &formatter, const std::string &name = "") : LogAppender(formatter, name)
        {
        }

    private:
    };

    class FileStreamAppender : public LogAppender
    {
    public:
        FileStreamAppender(const std::string &formatter, const std::string &name = "",
                           const std::string &fileName = "/home/lqf/cpp/Itachi/log/log.txt") : LogAppender(formatter, name),
                                                                                               m_fileName(fileName)

        {
        }

        ~FileStreamAppender()
        {
        }
        void log(const LogMessage &logMessage) override
        {
           {
                std::lock_guard<std::mutex> lock(m_mutex);//
                reopen();
                if (m_fstream.is_open())
                    m_formatter.format(logMessage, m_fstream);
                else{
                    std::cout<<"m_fstream not open"<<std::endl;
                }
           }
            //m_fstream.flush();
        }
        void reopen()
        {
            if(m_fstream.is_open())
            m_fstream.close();
            m_fstream.open(m_fileName,std::ios::out|std::ios::app);
        }

    private:
        std::mutex m_mutex;
        std::string m_fileName;
        std::fstream m_fstream;
    };

    class Logger
    {
    public:
        typedef std::shared_ptr<Logger> ptr;
        typedef std::unique_ptr<Logger> unique_ptr;
        typedef std::list<LogAppender::ptr> ListType;
        Logger()
        {
        }

        void addLogApppender(LogAppender::ptr pointer)
        {
            m_logAppenders.push_back(pointer);
        }

        void deleteLogAppender(LogAppender::ptr pointer)
        {
            for (auto it = m_logAppenders.begin(); it != m_logAppenders.end(); ++it)
            {
                if (*it == pointer)
                {
                    m_logAppenders.erase(it);
                    break;
                }
            }
        }

        void log(const LogMessage &logMessaage, const LogLevel::Level &level)
        {
            for (auto &val : m_logAppenders)
            {
                if (val->getLevel() <= level)
                {
                    val->log(logMessaage);
                }
            }
        }

    private:
        ListType m_logAppenders;
    };

    class LogAppenderDefiner
    {
    public:
        LogAppenderDefiner() : m_name(""),
                               m_type("stdstreasm"),
                               m_filePath(""),
                               m_level("DEBUG")
        {
        }
        bool operator==(const LogAppenderDefiner &b) const
        {
            return m_name == b.m_name &&
                   m_type == b.m_type &&
                   m_filePath == b.m_filePath &&
                   m_level == b.m_level;
        }

        bool operator>(const LogAppenderDefiner &b) const
        {
            return m_name > b.m_name &&
                   m_type > b.m_type &&
                   m_filePath > b.m_filePath &&
                   m_level > b.m_level;
        }

        bool operator<(const LogAppenderDefiner &b)
        {
            return m_name < b.m_name &&
                   m_type < b.m_type &&
                   m_filePath < b.m_filePath &&
                   m_level < b.m_level;
        }

        std::string getName() const
        {
            return m_name;
        }
        std::string getType() const
        {
            return m_type;
        }
        std::string getFilePath() const
        {
            return m_filePath;
        }
        LogLevel::Level getLevel() const
        {
            return LogLevel::FromString(m_level);
        }
        std::string getFormate() const
        {
            return m_formate;
        }

        void setName(const std::string &value) { m_name = value; }
        void setType(const std::string &value) { m_type = value; }
        void setFilePath(const std::string &value) { m_filePath = value; }
        void setLevel(const std::string &value) { m_level = value; }
        void FromString(const std::string &From)
        {
            nlohmann::json from = nlohmann::json::parse(From);
            if (!from["name"].is_null())
                from.at("name").get_to(m_name);
            if (!from["type"].is_null())
                from.at("type").get_to(m_type);
            if (!from["filepath"].is_null())
                from.at("filepath").get_to(m_filePath);
            if (!from["level"].is_null())
                from.at("level").get_to(m_level);
            if (!from["formate"].is_null())
                from.at("formate").get_to(m_formate);
            std::transform(m_type.begin(), m_type.end(), m_type.begin(), ::tolower);
        }

        std::string ToString() const
        {
            std::ostringstream oss;
            oss << "{"
                << "name: " << m_name << " "
                << "type: " << m_type << " "
                << "filepath: " << m_filePath << " "
                << "level: " << m_level << " "
                << "formate: " << m_formate
                << "}";
            return oss.str();
        }

    private:
        std::string m_name;
        std::string m_type;
        std::string m_filePath;
        std::string m_level;
        std::string m_formate;
    };

    class LogManager
    {
    public:
        LogManager(const LogManager &) = delete;
        LogManager &operator=(const LogManager &) = delete;

        void addLogApppender(LogAppender::ptr pointer)
        {
            m_logger->addLogApppender(pointer);
        }

        static LogManager &getInstance()
        {
            static LogManager logManager;
            return logManager;
        }

        void log(const LogMessage &logMessaage, const LogLevel::Level &level)
        {
            m_logger->log(logMessaage, level);
        }

    private:
        static void init();

        LogManager()
        {
            m_logger.reset(new Logger);
            init();
        }

        ~LogManager()
        {
        }

    private:
        static Logger::ptr m_logger;
    };

    class LogWraper
    {
    public:
        LogWraper(const std::string &level,
                  const char *file,
                  int line)
            : m_level(LogLevel::FromString(level)),
              m_logMessage(m_level, file, line)
        {
        }
        ~LogWraper()
        {
            LogManager::getInstance().log(m_logMessage, m_level);
        }
        std::ostream &operator<<(const std::string &message)
        {
            m_logMessage << message;
            return m_logMessage.getMessageStream();
        }

    private:
        LogLevel::Level m_level;
        LogMessage m_logMessage;
    };

}
#endif