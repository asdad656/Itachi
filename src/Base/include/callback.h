/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 16:30:41
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 19:07:06
 * @Description: 
 */
#ifndef __CALLBACK__H__
#define __CALLBACK__H__
#include<functional>
namespace Itachi{
    using readableCallBack=std::function<void(const int&)>;
    using writeableCallBack=std::function<void(const int&)>;
    using errorableCallBack=std::function<void(const int&)>;
    using closeableCallBack=std::function<void(const int&)>;

}


#endif