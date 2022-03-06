/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-04 21:38:33
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-06 23:20:50
 * @Description: 
 */
#ifndef __DEFINITION__H__
#define __DEFINITION__H__
#include<logger.h>
#include<assert.h>

//------------------------------logger------------------------ ------------//
#define __INIT__                                                                     \
    Itachi::LogManager::getInstance();                                        \
 
#define LOG(LEVEL)                                                                \
    Itachi::LogWraper(#LEVEL,__FILE__,__LINE__)


#define LOG_DEBUG  LOG(DEBUG)

#define LOG_INFO  LOG(INFO)

#define LOG_WARN  LOG(WARN)

#define LOG_ERROR  LOG(ERROR)

#define LOG_FATAL  LOG(FATAL)


//------------------------------assert-----------------------------------//
#ifdef  DEBUG
    #define ASSERT(CONDITION)                                                 \
        if(!CONDITION)                                                                  \
            {                                                                                  \
                LOG_FATAL<<"ASSERT FAILED:  "<<#CONDITION;      \
                assert(CONDITION);                                                  \
            }
#else
    #define ASSERT(CONDITION)                                                \

#endif



#endif