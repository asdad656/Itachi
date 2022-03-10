/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-10 16:05:30
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 20:56:29
 * @Description: 
 */
#include "channel.h"
#include "config.h"
#include "definition.h"
#include "EventLoop.h"
#include <sys/timerfd.h>
#include "threadpool_c++11.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Tcpserver.h"
#include "buffer.h"
#include "tcpConnection.h"
using namespace Itachi;
void test(void)
{
    LOG_DEBUG << "time out!";
}

void *addtask(void *hhh)
{
    EventLoop *pp = static_cast<EventLoop *>(hhh);
    pp->runInLoop(test);
}
void testMessageCallBack(std::shared_ptr<TcpConnection> ptr, Buffer *buf, int timeStemp)
{
    std::string str=buf->readAllAsString();
    LOG_DEBUG<<"recv message: "<<str;
    ptr->send(str);
}
int main()
{

    Config::LoadFromJson("/home/lqf/cpp/Itachi/config.json");
    sockaddr_in *addr = new sockaddr_in;
    addr->sin_family = AF_INET;
    addr->sin_port = htons(5555);
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    TcpServer tcpserver(addr, "ItchiServer");
    tcpserver.setMessageCallBack(testMessageCallBack);
    tcpserver.start();
}