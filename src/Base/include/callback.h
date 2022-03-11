/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 16:30:41
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 11:29:51
 * @Description: 
 */
#ifndef __CALLBACK__H__
#define __CALLBACK__H__
#include<functional>
#include<memory>
struct sockaddr_in;
namespace Itachi{
    class TcpConnection;
    class Buffer;
    class TimeStamp;
    using readableCallBack=std::function<void()>;
    using writeableCallBack=std::function<void()>;
    using errorableCallBack=std::function<void()>;
    using closeableCallBack=std::function<void()>;
    using TcpConnectionCallBack=std::function<void(std::shared_ptr<TcpConnection>)>;
    using TcpCloseCallBack=std::function<void(std::shared_ptr<TcpConnection>,const TimeStamp& timeStemp)>;
    using TcpReadCallBack=std::function<void(std::shared_ptr<TcpConnection>,const TimeStamp& timeStemp)>;
    using TcpErrorCallBack=std::function<void(std::shared_ptr<TcpConnection>,const TimeStamp& timeStemp)>;
    using TcpMessaageCallBack=std::function<void(std::shared_ptr<TcpConnection>,Buffer*,const TimeStamp& timeStemp)>;
    using  AdaptorReadCallBack=std::function<void(int,sockaddr_in*)>;
}


// auto x=[](auto  param){
//     //func(param)
// }
// auto xx=[](auto &&param){
//     //func(std::formardd< dctltype(paraam)>(paaram))
// }

// template<class T>
// operator()(T param)const{
//     //func(param)
// }




#endif