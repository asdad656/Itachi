/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-05 23:53:15
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 18:42:08
 * @Description: 
 */
#include "threadpool_c++11.h"
#include <mutex>
#include <condition_variable>
#include <thread>
#include <memory>
#include <atomic>
#include <functional>
#include "definition.h"
#include "EventLoop.h"
namespace Itachi
{
    static thread_local std::thread::id _Current_thread__t_id = std::thread::id(0);
    static thread_local std::string _Current_thread__t_name = "main  thread";
    void ThreadPool::addTask(Task *task)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        //astd::shared_ptr<Task> ptr(task);
        m_taskQueue.emplace(task);
        //    if(m_idelThreadCount)
        if (m_taskQueue.size() == 1)
        {
            m_condition_variable.notify_one();
        }
    }

    void ThreadPool::addTask(std::function<void *(void *)> cb, void *args, int8_t priority)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_taskQueue.emplace(new Task(cb, args, priority));
        if (m_idelThreadCount != 0)
        {
            m_condition_variable.notify_one();
        }
    }

    std::shared_ptr<Task> ThreadPool::takeTask()
    {
        if (!m_taskQueue.empty())
        {
            auto ptr = m_taskQueue.top();
            m_taskQueue.pop();
            return ptr;
        }
        return nullptr;
    }

    void ThreadPool::stop()
    {
        m_stop = true;
        m_condition_variable.notify_all();
    }

    void ThreadPool::start()
    {
        if (m_stop)
        {
            m_stop = false;
            for (int i = 0; i < m_threadMaxCount; ++i)
            {
                m_threads.emplace_back(new Thread(std::bind(&ThreadPool::execuate, std::placeholders::_1,m_name + std::to_string(i)),
                                                  static_cast<void *>(this),
                                                  m_name + std::to_string(i)));
            }
        }
    }

    void *ThreadPool::execuate(void *threadPool, const std::string &name)
    {
        ThreadPool *m_threadPool = static_cast<ThreadPool *>(threadPool);
        setCurrentThreadId(std::this_thread::get_id());
        setCurrentThreadName(name);
        while (true)
        {
            std::shared_ptr<Task> m_task = nullptr;
            {
                std::unique_lock<std::mutex> lock(m_threadPool->m_mutex); //
                while (m_threadPool->m_taskQueue.empty() && !m_threadPool->m_stop)
                {
                    ++m_threadPool->m_idelThreadCount;
                    m_threadPool->m_condition_variable.wait(lock);
                    --m_threadPool->m_idelThreadCount;
                }
                if (m_threadPool->m_taskQueue.empty() || m_threadPool->m_stop)
                    break;
                else
                {
                    m_task = m_threadPool->takeTask();
                }
            }
            if (m_task)
            {
                (*m_task)();
            }
        }
    }

    std::thread::id getCurrentThreadId()
    {
        return _Current_thread__t_id;
    }
    std::string getCurrentThreadName()
    {
        return _Current_thread__t_name;
    }

    void setCurrentThreadName(const std::string &name)
    {
        _Current_thread__t_name = name;
    }
    void setCurrentThreadId(const std::thread::id &id)
    {
        _Current_thread__t_id = id;
    }

    ThreadPool_eventLoop::ThreadPool_eventLoop(int default_threadCounts) : m_starting(false),
                                                                           m_maxThreadCount(default_threadCounts)
    {
        m_eventLoops.reserve(default_threadCounts);
        m_threads.reserve(default_threadCounts);
    }

    ThreadPool_eventLoop::~ThreadPool_eventLoop()
    {
        stop();
    }

    void ThreadPool_eventLoop::start()
    {
        m_starting = true;
        LOG_DEBUG << "ThreadPool_eventLoop start!!!";
        for (int i = 0; i < m_maxThreadCount; ++i)
        {
            m_threads.push_back(std::make_shared<Thread>(
                std::bind(&ThreadPool_eventLoop::execuate,std::placeholders::_1,"ThreadPool_eventLoop  " + std::to_string(i)),
                static_cast<void*>(this),
                "ThreadPool_eventLoop  " + std::to_string(i)));
        }
    }
    void ThreadPool_eventLoop::stop()
    {
        for (auto &val : m_eventLoops)
        {
            if (val)
            {
                val->stop();
            }
        }
        for (auto &val : m_threads)
        {
            if (val)
                val->join();
        }
    }
    EventLoop *ThreadPool_eventLoop::getALoop() const
    {
        static std::atomic<int> index{0};
        auto it = m_eventLoops[index].get();
        index = (index + 1) % m_eventLoops.size();
        return it;
    }
    void *ThreadPool_eventLoop::execuate(void *arg, const std::string &name)
    {
        setCurrentThreadId(std::this_thread::get_id());
        setCurrentThreadName(name);
        auto it = static_cast<ThreadPool_eventLoop *>(arg);
        if (it == nullptr)
            return 0;
        EventLoop *thread_loop = new EventLoop();
        {
            std::lock_guard<std::mutex> Lock(it->m_mutex);
            it->m_eventLoops.emplace_back(thread_loop);
        }
        LOG_DEBUG << "thread_loop begin";
        thread_loop->loop();
        LOG_DEBUG << "thread_loop finish";
        return 0;
    }
}