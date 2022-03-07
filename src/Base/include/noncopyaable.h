/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 19:32:49
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 19:35:15
 * @Description: 
 */
#ifndef __NONCOPYABLE__H__
#define __NONCOPYABLE__H__
namespace Itachi
{
    class nonCopyable
    {
    public:
        nonCopyable() = default;
        virtual ~nonCopyable() = default;
        nonCopyable(const nonCopyable &) = delete;
        nonCopyable &operator=(const nonCopyable &)=delete;
        nonCopyable(nonCopyable&&)=delete;
    };
}

#endif
