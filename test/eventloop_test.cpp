/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-08 15:39:05
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-08 18:08:07
 * @Description: 
 */
#include "channel.h"
#include "config.h"
#include "definition.h"
#include "EventLoop.h"
#include <sys/timerfd.h>
#include"threadpool_c++11.h"
using namespace Itachi;
void test(void)
{
    LOG_DEBUG << "time out!";
}

void*addtask(void*hhh){
    EventLoop*pp=static_cast<EventLoop*>(hhh);
    pp->runInLoop(test);
}
int main()
{

    Config::LoadFromJson("/home/lqf/cpp/Itachi/config.json");
    // int fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    EventLoop loop;
    // Channel channle(&loop, fd);
    // channle.setReadCallback(test);
    // channle.enableRead();

    // struct itimerspec howlong;
    // memset(&howlong, 0, sizeof(howlong));
    // howlong.it_value.tv_sec = 5;
    // timerfd_settime(fd, 0, &howlong, NULL);
    ThreadPool threadPool("lqfadsf");
    threadPool.addTask(
        addtask,&loop
    );
        threadPool.addTask(
        addtask,&loop
    );

        threadPool.addTask(
        addtask,&loop
    );

        threadPool.addTask(
        addtask,&loop
    );


    threadPool.addTask(
        addtask,&loop
    );

        threadPool.addTask(
        addtask,&loop
    );


        threadPool.addTask(
        addtask,&loop
    );


        threadPool.addTask(
        addtask,&loop
    );


        threadPool.addTask(
        addtask,&loop
    );



        threadPool.addTask(
        addtask,&loop
    );
    loop.loop();
    // ::close(fd);
}