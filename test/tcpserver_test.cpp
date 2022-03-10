/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-10 16:05:30
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 17:15:37
 * @Description: 
 */
#include "channel.h"
#include "config.h"
#include "definition.h"
#include "EventLoop.h"
#include <sys/timerfd.h>
#include"threadpool_c++11.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include"Tcpserver.h"
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

    // Channel channle(&loop, fd);
    // channle.setReadCallback(test);
    // channle.enableRead();

    // struct itimerspec howlong;
    // memset(&howlong, 0, sizeof(howlong));
    // howlong.it_value.tv_sec = 5;
    // timerfd_settime(fd, 0, &howlong, NULL);

    // ::close(fd);
        sockaddr_in *addr = new sockaddr_in;
        addr->sin_family = AF_INET;
        addr->sin_port =htons(5555);
        addr->sin_addr.s_addr =  htonl(INADDR_ANY);
        TcpServer tcpserver(addr,"ItchiServer");
        tcpserver.start();
 }