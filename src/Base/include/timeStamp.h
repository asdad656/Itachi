/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-01-27 21:59:17
 * @LastEditors: lqf
 * @LastEditTime: 2022-02-08 06:12:05
 * @Description: 
 */
#ifndef __TIMESTAMP__H__
#define __TIMESTAMP__H__
#include<time.h>
#include<stdint.h>
#include<algorithm>
namespace Itachi{
    class TimeStamp{
    public:
        TimeStamp():
        m_microSecond(0)
        {    
        }
         TimeStamp(int64_t microSecond):
        m_microSecond(microSecond){

        }
        bool operator <(const TimeStamp&b)const{
            return m_microSecond<b.m_microSecond;
        }
        bool operator==(const TimeStamp&b)const{
            return m_microSecond==b.microSecondPerSecond;
        }
        int64_t getMicroSecond()const{return m_microSecond;}
        int64_t getSecond()const{return m_microSecond/microSecondPerSecond;}
        bool isVaild()const{return m_microSecond>0;}


        static TimeStamp fromUnixTime(time_t t){
            return fromUnixTime(t,0);
        }
        static TimeStamp fromUnixTime(time_t t,int microseconds){
            return TimeStamp(static_cast<int64_t>(t)*microSecondPerSecond+microseconds);
        }
        static TimeStamp now();
        static TimeStamp invaild(){ return TimeStamp();}
        static const int microSecondPerSecond=1000*1000;
        void swap(TimeStamp&s){
            std::swap(m_microSecond,s.m_microSecond);
        }
    private:
        int64_t m_microSecond;
    };
    inline TimeStamp addTime(TimeStamp timestamp,double seconds){
        int64_t delta=static_cast<int64_t>(seconds*TimeStamp::microSecondPerSecond);
        return TimeStamp(timestamp.getMicroSecond()+delta);
    }
}
#endif
