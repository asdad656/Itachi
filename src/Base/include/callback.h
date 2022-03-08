/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 16:30:41
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-08 16:28:00
 * @Description: 
 */
#ifndef __CALLBACK__H__
#define __CALLBACK__H__
#include<functional>
namespace Itachi{
    using readableCallBack=std::function<void()>;
    using writeableCallBack=std::function<void()>;
    using errorableCallBack=std::function<void()>;
    using closeableCallBack=std::function<void()>;

}


#endif