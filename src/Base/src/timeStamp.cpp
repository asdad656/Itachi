/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-01-27 21:59:08
 * @LastEditors: lqf
 * @LastEditTime: 2022-01-27 22:14:00
 * @Description: 
 */
#include"timeStamp.h"
#include<sys/time.h>
namespace Itachi{
     TimeStamp TimeStamp::now(){
         struct timeval t;
         gettimeofday(&t,NULL);
         int64_t seconds=t.tv_sec;
         return TimeStamp(seconds*microSecondPerSecond+t.tv_usec);
     }

}