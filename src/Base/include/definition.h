/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-04 21:38:33
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-05 13:48:38
 * @Description: 
 */
#ifndef __DEFINITION__H__
#define __DEFINITION__H__
#include<logger.h>

#define __INIT__                                    \
    Itachi::LogManager::getInstance();      \



    
#define LOG(LEVEL)  \
    Itachi::LogWraper(#LEVEL,__FILE__,__LINE__)


#define LOG_DEBUG  LOG(DEBUG)

#define LOG_INFO  LOG(INFO)

#define LOG_WARN  LOG(WARN)

#define LOG_ERROR  LOG(ERROR)

#define LOG_FATAL  LOG(FATAL)

#endif