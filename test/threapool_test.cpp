/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-06 01:00:14
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-06 01:16:46
 * @Description: 
 */
#include "threadpool_c++11.h"
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace Itachi;

void *task(void *)
{
    std::cout << ThreadPool::getCurrentThreadId() << "   " << ThreadPool::getCurrentThreadName() << std::endl;
}

int main()
{
    ThreadPool threadPool;
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
    sleep(10);
    // std::this_thread::sleep(1000000);
    return 0;
}