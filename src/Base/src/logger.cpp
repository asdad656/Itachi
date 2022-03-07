/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-03 17:09:30
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 15:35:48
 * @Description: 
 */
#include "../include/logger.h"
#include <string>
#include <sstream>
#include <memory>
#include <fstream>
#include <functional>
#include "config.h"
#include "threadpool_c++11.h"
namespace Itachi
{

    std::string LogLevel::ToString(const LogLevel::Level &level)
    {
#define XX(ARG, STANDERED)          \
    if (ARG == LogLevel::STANDERED) \
        return #STANDERED;
        XX(level, ALL);
        XX(level, DEBUG);
        XX(level, INFO);
        XX(level, WARN);
        XX(level, ERROR);
        XX(level, FATAL);
        XX(level, OFF);
        XX(LogLevel::WRONGLEVEL, WRONGLEVEL);
#undef XX
    }

    LogLevel::Level LogLevel::FromString(const std::string &level)
    {
        std::string Level = level;
        std::transform(Level.begin(), Level.end(), Level.begin(), ::toupper);
#define XX(STANDARD)        \
    if (#STANDARD == Level) \
        return LogLevel::STANDARD;

        XX(ALL)
        XX(DEBUG)
        XX(INFO)
        XX(WARN)
        XX(ERROR)
        XX(FATAL)
        XX(OFF)
#undef XX
        return LogLevel::WRONGLEVEL;
    }


    LogMessage::LogMessage(const LogLevel::Level &level,
                const char *file,
                int line) : m_level(level),
                            m_file(file),
                            m_line(line),
                            m_time(time(NULL)),
                            m_threadId(getCurrentThreadId()),
                            m_threadName(getCurrentThreadName())
    {
    }


    class LogLevelFormater : public LogFormatter::LogItemFormatter
    {
    public:
        LogLevelFormater(const std::string &conditionOrformat) : LogItemFormatter(conditionOrformat)
        {
        }
        /**
     * @description:                                    输出日志的级别
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */
        void operator()(const LogMessage &logMessage, std::ostream &os) const override
        {
            os << LogLevel::ToString(logMessage.getLevel());
        }

    private:
    };

    class LogMessageFormatter : public LogFormatter::LogItemFormatter
    {
    public:
        LogMessageFormatter(const std::string &conditionOrformat) : LogItemFormatter(conditionOrformat)
        {
        }
        /**
     * @description:                                    输出日志的消息体
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */
        void operator()(const LogMessage &logMessage, std::ostream &os) const override
        {
            os << logMessage.getMessage();
        }

    private:
    };

    class LogTimeFormatter : public LogFormatter::LogItemFormatter
    {
    public:
        LogTimeFormatter(const std::string &conditionOrformat = "%Y-%m-%d %H:%M:%S") : LogItemFormatter(conditionOrformat)
        {
            m_conditionOrformat = "%Y-%m-%d %H:%M:%S";
        }
        /**
     * @description:                                    输出日志的日期
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */
        void operator()(const LogMessage &logMessage, std::ostream &os) const override
        {
            const time_t &time = logMessage.getTime();
            struct tm time_formater;
            localtime_r(&time, &time_formater);
            char timeformatter[48];
            strftime(timeformatter, sizeof(timeformatter), m_conditionOrformat.c_str(), &time_formater);
            os << timeformatter;
        }
    };

    class LogFilePathFormatter : public LogFormatter::LogItemFormatter
    {
    public:
        LogFilePathFormatter(const std::string &conditionOrformat) : LogItemFormatter(conditionOrformat)
        {
        }
        /**
     * @description:                                    输出日志的年份
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */
        void operator()(const LogMessage &logMessage, std::ostream &os) const override
        {
            os << logMessage.getFile();
        }

    private:
    };

    class LogLineFormatter : public LogFormatter::LogItemFormatter
    {
    public:
        LogLineFormatter(const std::string &)
        {
        }
        /**
     * @description:                                    输出日志的年份
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */
        void operator()(const LogMessage &logMessage, std::ostream &os) const override
        {
            os << logMessage.getLine();
        }

    private:
    };

    class LogCharacterFormatter : public LogFormatter::LogItemFormatter
    {
    public:
        LogCharacterFormatter(const std::string &conditionOrformat) : LogItemFormatter(conditionOrformat)
        {
        }
        /**
     * @description:                                    输出日志的年份
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */
        void operator()(const LogMessage &logMessage, std::ostream &os) const override
        {
            os << m_conditionOrformat;
        }

    private:
    };

    class LogNewLineFormatter : public LogFormatter::LogItemFormatter
    {
    public:
        LogNewLineFormatter(const std::string &)
        {
        }
        /**
     * @description:                                    输出日志的年份
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */
        void operator()(const LogMessage &logMessage, std::ostream &os) const override
        {
            os << std::endl;
        }

    private:
    };

    class LogThreadIdFormatter : public LogFormatter::LogItemFormatter
    {
    public:
        LogThreadIdFormatter(const std::string &)
        {
        }
        /**
     * @description:                                    输出日志的年份
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */
        void operator()(const LogMessage &logMessage, std::ostream &os) const override
        {
            os << logMessage.getThreadId();
        }

    private:
    };

    class LogThreadNameFormatter : public LogFormatter::LogItemFormatter
    {
    public:
        LogThreadNameFormatter(const std::string &)
        {
        }
        /**
     * @description:                                    输出日志的年份
     * @param LogMessage&logMessag      日志
     * @param std::ostream&os                  输出流   
     * @return void
     */
        void operator()(const LogMessage &logMessage, std::ostream &os) const override
        {
            os << logMessage.getThreadName();
        }

    private:
    };
    //%m 消息体
    //%p  level
    //%r   启动后的时间
    //%c   分割符号
    //%t    县城id
    //%u 线程name
    //%n   回车
    //%d   时间戳
    //%f    文件名
    //%l    行号
    //%N 线程name

    void LogFormatter::init()
    {
        size_t right = 0;
        size_t left = 0;
        size_t length = m_formatter.size();
        std::string itemFormatter = "";
        while (right < length || left < length)
        {
            while (right < length && m_formatter[right] != '%')
            {
                ++right;
            }

            if (m_formatter[left] != '%')
            {
                itemFormatter = m_formatter.substr(left, right - left);
                left = right++;
            }
            else
            {
                itemFormatter = m_formatter.substr(left, 2);
                left += 2;
            }

#define XX(PATTERN, FORMATER_CLASS)                                 \
    if (itemFormatter == #PATTERN || #PATTERN == "%c")           \
    {                                                                                         \
        addItemFormatter(new FORMATER_CLASS(itemFormatter)); \
        continue;                                                                          \
    }
            XX(%f, LogFilePathFormatter)
            XX(%p, LogLevelFormater)
            XX(%m, LogMessageFormatter)
            XX(%l, LogLineFormatter)
            XX(%d, LogTimeFormatter)
            XX(%n, LogNewLineFormatter)
            XX(%u, LogThreadNameFormatter)
            XX(%t, LogThreadIdFormatter)
            XX(%c, LogCharacterFormatter)
#undef XX
        }
    }

    //-------------------------------LogManager-----------------------------//
    Logger::ptr LogManager::m_logger = nullptr;

    //---------------------------------------loginit----------------------------------------//
    ConfigVar<std::vector<LogAppenderDefiner>>::ptr vec_loggers =
        Config::LookUp(".lqf.loggers", std::vector<LogAppenderDefiner>{});

    auto logInitCallBack =
        [](const std::vector<LogAppenderDefiner> &old_val, const std::vector<LogAppenderDefiner> &new_val)
    {
        // 删除新的中不存在的     删除新的中重复的
        // for (auto it = old_val.begin(); it != old_val.end();)
        // {
        //     auto it2 = new_val.begin();
        //     for (; it2 != new_val.end(); ++it2)
        //     {
        //         if (*it == *it2)
        //         {
        //             new_val.erase(it2);
        //             break;
        //         }
        //     }
        //     if (it2 != new_val.end())
        //     {
        //         old_val.erase(it);
        //     }
        //     else
        //     {
        //         ++it;
        //     }
        // }
        //添加新的
        for (const auto &val : new_val)
        {
            LogAppender::ptr pointer = nullptr;
            if (val.getType() == "filestream")
            {
                pointer.reset(new FileStreamAppender(val.getFormate(), val.getName(), val.getFilePath()));
            }
            else
            {
                pointer.reset(new StdOutAppender(val.getFormate(), val.getName()));
            }
            pointer->setLevel(val.getLevel());
            LogManager::getInstance().addLogApppender(pointer);
        }
    };

    void LogManager::init()
    {
        vec_loggers->addCallBack(logInitCallBack);
    }
}