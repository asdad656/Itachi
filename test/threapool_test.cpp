/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-06 01:00:14
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-06 12:37:53
 * @Description: 
 */
#include "threadpool_c++11.h"
#include <iostream>
#include <unistd.h>
#include"config.h"
#include"definition.h"
using namespace std;
using namespace Itachi;

void *task(void *)
{
    LOG_ERROR<<"test thread pool:   "<<getCurrentThreadName()<<"  :   "<<getCurrentThreadId();
}

int main()
{
        Config::LoadFromJson("/home/lqf/cpp/Itachi/config.json");
         LOG_DEBUG<<"test thread pool:   "<<getCurrentThreadName()<<"  :   "<<getCurrentThreadId()<<std::endl;
    ThreadPool threadPool("lqf",30,true);
    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);

    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);
    threadPool.addTask(task, nullptr);
    // std::this_thread::sleep(1000000);
    return 0;
}