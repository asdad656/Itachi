/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-11 09:56:31
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 21:26:37
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
#include "timeStamp.h"
#include "httpServer.h"
using namespace Itachi;
using namespace Itachi::http;
#include "adaptor.h"

// void connectionCallBack(const std::shared_ptr<TcpConnection> &ptr){
//       std::stringstream ss;
//       ss<<"welcome to server: "<<ptr->getName()<<std::endl;
//      ptr->send(ss.str());
// }
// void messageCallBack(const std::shared_ptr<Itachi::net::TcpConnection> &ptr,Buffer*buf,TimeStamp now){
//    std::string meeesgae(buf->retrieveAllasString());
//    meeesgae+=" time: "+std::to_string(now.getMicroSecond());
//    std::cout<<meeesgae<<std::endl;
//    ptr->send(meeesgae);
// }
// void httpResponseCallback(const std::shared_ptr<Itachi::net::TcpConnection> &ptr){
//     stringstream ss;
//     ss<<"HTTP/1.1 200 OK"
//     <<"\r\n"
//     <<"Accept-Encoding:gzip, deflate"
//     <<"\r\n"
//     <<"Server:Jackey_1.0"
//     <<"\r\n"
//     <<"connection:close"
//     <<"\r\n"
//     <<"content-length:26"
//     <<"\r\n"
//     <<"\r\n"
//     <<"\r\n"
//     <<"welcome to Server_Itachi!!";
//     ptr->send(ss.str());
// }
// void* run(void*arg){
//     // short *port=static_cast<short*>(arg);
//     // EventLoop *work_loop=new EventLoop();
//     // sockaddr_in addr;
//     // addr.sin_family=AF_INET;
//     // addr.sin_port=htons(*port);
//     // addr.sin_addr.s_addr=INADDR_ANY;
//     // TcpServer::ptr tcpserver(new TcpServer((sockaddr*)&addr,"server echoes"));
//     // //tcps
//     // tcpserver->setConnectionCallBack(connectionCallBack);
//     // tcpserver->setMessageCallBack(messageCallBack);
//     // tcpserver->start();
//     // work_loop->loop();
// }
// void* httpResponse(void*arg){
//     // short *port=static_cast<short*>(arg);
//     // EventLoop *work_loop=new EventLoop();
//     // sockaddr_in addr;
//     // addr.sin_family=AF_INET;
//     // addr.sin_port=htons(*port);
//     // addr.sin_addr.s_addr=INADDR_ANY;
//     // TcpServer::ptr tcpserver(new TcpServer(work_loop,(sockaddr*)&addr,"server echoes"));
//     // //tcps
//     // tcpserver->setConnectionCallBack(httpResponseCallback);

//     // tcpserver->start();
//     // work_loop->loop();
// }

// void test(void)
// {
//     LOG_DEBUG << "time out!";
// }

// void *addtask(void *hhh)
// {
//     EventLoop *pp = static_cast<EventLoop *>(hhh);
//     pp->runInLoop(test);
// }
// void testMessageCallBack(std::shared_ptr<TcpConnection> ptr, Buffer *buf,const  TimeStamp& timeStemp)
// {
//     std::string str=buf->readAllAsString();
//     LOG_DEBUG<<"recv message: "<<str;
//     ptr->send(str);
//
int main()
{
    Config::LoadFromJson("/home/lqf/cpp/Itachi/config.json");
    HttpServer httpserver;
    httpserver.start();
}