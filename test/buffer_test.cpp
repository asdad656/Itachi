/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 14:37:22
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 15:24:48
 * @Description: 
 */
#include"buffer.h"
#include<iostream>
#include"config.h"
using namespace Itachi;
using namespace std;
int main(){
    Config::LoadFromJson("/home/lqf/cpp/Itachi/config.json");
    Buffer buffer;
    LOG_DEBUG<<"buffer readable: "<<buffer.readableBuffer();
    LOG_DEBUG<<"buffer maxWriteaableSIze: "<<buffer.maxWriteaableSIze();
    LOG_DEBUG<<"buffer maxBufferSIze: "<<buffer.maxBufferSIze();
    
    char s[]="asdfsadfasdfasdasdf";
    buffer.write(s,sizeof(s));
    LOG_DEBUG<<"test buffer:1 "<<buffer.readAsString(6);
    LOG_DEBUG<<"test buffer:2 "<<buffer.readAsString(14);


    LOG_DEBUG<<"buffer readable: "<<buffer.readableBuffer();
    LOG_DEBUG<<"buffer maxWriteaableSIze: "<<buffer.maxWriteaableSIze();
    LOG_DEBUG<<"buffer maxBufferSIze: "<<buffer.maxBufferSIze();

   // LOG_DEBUG<<"test buffer:3 "<<buffer.readAsString(3);
    return 0;
}