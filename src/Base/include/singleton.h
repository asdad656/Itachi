/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-03 17:07:37
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 09:46:13
 * @Description: 
 */  
#ifndef __SINGLETON__H__
#define __SINGLETON__H__
#include<memory>
namespace Itachi{
    template<class T>
    using  TValue=std::shared_ptr<T>;
    template<class T>
    class SingLeton{
    public:
        static T&getInstance(){
            static T value;
            return value;
        }
    private:
        SingLeton(){}
        ~SingLeton(){}
        SingLeton(const SingLeton&)=delete;
        SingLeton&operator=(const SingLeton&)=delete;
    };
}


#endif