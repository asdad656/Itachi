/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-10 16:05:30
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 20:34:41
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
#include"timeStamp.h"
using namespace Itachi;
void test(void)
{
    LOG_DEBUG << "time out!";
}
class p{
public:
    p(){

        s=new TcpServer;
    }
    void start(){
        s->start();
    }
private:
    TcpServer*s;
};
void *addtask(void *hhh)
{
    EventLoop *pp = static_cast<EventLoop *>(hhh);
    pp->runInLoop(test);
}
void testMessageCallBack(std::shared_ptr<TcpConnection> ptr, Buffer *buf,const  TimeStamp& timeStemp)
{
    std::string str=buf->readAllAsString();
    LOG_DEBUG<<"recv message: "<<str;
    ptr->send(str);
}
int main()
{

    Config::LoadFromJson("/home/lqf/cpp/Itachi/config.json");
    // sockaddr_in *addr = new sockaddr_in;
    // addr->sin_family = AF_INET;
    // addr->sin_port = htons(5555);
    // // addr->sin_addr.s_addr = htonl(INADDR_ANY);
    // TcpServer *tcpserver=new TcpServer;//(addr, "ItchiServer");
    // // tcpserver.setMessageCallBack(testMessageCallBack);
    // tcpserver->start();
    p l;
    l.start();
}