/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-03 17:13:23
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 15:12:14
 * @Description: 
 */
#ifndef __THREADAPOOL__C11__H__
#define __THREADAPOOL__C11__H__
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <memory>
#include <queue>
#include <atomic>
#include <vector>
//std::mutex                    互斥锁
//std::recursive_mutex      第归锁

//std::lock_guard    std::adopt_lock   需要提前自己加锁 std::defer_lock 不获得锁，但是后续需要自己加锁  例如 lock  teylock   所有权传递简单  realese s释放所有权，需要自己届缩

//std::condition_variable   1.默认传递的对象是unique——lock   wait会释放锁  并且阻塞当前线程，知道杯notify   wait的第二个参数为faalse的时候才会进入阻塞状态否则不会

//wait——for   的第二个参数传递时间  每当时间超过或者杯唤醒，即可和wait一样的步骤继续
//notify——all at threaad exit
namespace Itachi
{

    struct Task
    {
        typedef std::unique_ptr<Task> unique_ptr;
        Task()
        {
        }
        Task(std::function<void *(void *)> &cb, void *args, int8_t priority = 0) : args(args),
                                                                                  cb(cb),
                                                                                  priority(priority > 5 ? 5 : (priority < 0 ? 0 : priority))
        {
        }
        Task(std::function<void *(void *)> &&cb, void *args, int8_t priority = 0) : args(args),
                                                                                cb(cb),
                                                                                priority(priority > 5 ? 5 : (priority < 0 ? 0 : priority))
        {
        }
        void *operator()()
        {
            if (cb)
                return cb(args);
            return nullptr;
        }

        bool operator>(const Task &b) const
        {
            return priority > b.priority;
        }

        bool operator<(const Task &b) const
        {
            return priority > b.priority;
        }

        void *args = nullptr;
        std::function<void *(void *)> cb = nullptr;
        int8_t priority = 0;
    };

    class Thread
    {
    public:
        typedef std::shared_ptr<Thread> ptr;
        enum ThreadState
        {
            NEW,
            READY,
            EXECUT,
            IDLE,
            FINISH,
            WRONG
        };
        Thread() : m_id(std::thread::id()),
                   m_thread(nullptr),
                   m_task(nullptr),
                   m_name("")
        {
        }
        Thread(std::function<void *(void *)> cb, void *args, const std::string &name) : 
                                                                                        m_task(new Task(std::move(cb), args)),
                                                                                        m_name(name)
        {
            m_state = NEW;
            m_thread.reset(new std::thread((*m_task)));
            m_state = EXECUT;
        }

        Thread(std::function<void *(void *)> &&cb, void *args, std::string &&name) : 
                                                                                        m_task(new Task(std::move(cb), args)),
                                                                                        m_name(std::move(name))
        {
            m_state = NEW;
            m_thread.reset(new std::thread((*m_task)));
            m_state = EXECUT;
        }

        Thread(Task *task) : m_task(task)
        {
            join();
        }
        ~Thread()
        {
            m_state = FINISH;
            if (m_thread->joinable())
            {
                m_thread->join();
            }
        }
        bool isJoinable() const
        {
            if (m_thread)
                return m_thread->joinable();
            return false;
        }
        void join()
        {
            if (isJoinable())
            {
                m_thread->join();
            }
        }

    private:
        ThreadState m_state;
        std::thread::id m_id;
        Task::unique_ptr m_task;
        std::unique_ptr<std::thread> m_thread;
        std::string m_name;
    };

    struct taskQueue_cmp
    {
        bool operator()(const std::shared_ptr<Task> &a, const std::shared_ptr<Task> &b) const
        {
            return a.get() > b.get();
        };
    };

    class ThreadPool
    {
    public:
        ThreadPool(const std::string &name = "", int maxThreadCount = 10, bool autoStart = true) : m_name(name),
                                                                                                   m_threadMaxCount(maxThreadCount < 10 ? 10 : maxThreadCount),
                                                                                                   m_stop(!autoStart)
        {
            //m_threads.resize(maxThreadCount);
            if (autoStart)
                for (int i = 0; i < maxThreadCount; ++i)
                {
                    m_threads.emplace_back(new Thread(
                        std::bind(&ThreadPool::execuate,this,m_name+std::to_string(i)),
                                    static_cast<void*>(this),
                                    m_name+std::to_string(i)));
                }
        }

        ThreadPool(std::string &&name = "", int maxThreadCount = 10, bool autoStart = true) : m_name(name),
                                                                                                   m_threadMaxCount(maxThreadCount < 10 ? 10 : maxThreadCount),
                                                                                                   m_stop(!autoStart)
        {
            m_threads.resize(maxThreadCount);
            if (autoStart)
                for (int i = 0; i < maxThreadCount; ++i)
                {
                    m_threads.emplace_back(new Thread(std::bind(&ThreadPool::execuate,this,m_name+std::to_string(i)),
                                                        static_cast<void*>(this),
                                                        m_name+std::to_string(i)));
                }
        }

        ~ThreadPool()
        {
            m_stop = true;
            m_condition_variable.notify_all();
        }
        void addTask(Task *task);
        void addTask(std::function<void *(void *)> cb, void *args, int8_t priority = 0);
        void start();
        void stop();
        std::shared_ptr<Task> takeTask();

    private:
        static void *execuate(void *, const std::string &);


    private:
        std::string m_name;
        std::atomic<bool> m_stop{false};
        std::atomic<int> m_idelThreadCount{0};
        uint32_t m_threadMaxCount;
        std::mutex m_mutex;
        std::condition_variable m_condition_variable;
        std::priority_queue<std::shared_ptr<Task>, std::vector<std::shared_ptr<Task>>, taskQueue_cmp> m_taskQueue;
        std::vector<Thread::ptr> m_threads;
    };

    std::thread::id getCurrentThreadId();
    std::string getCurrentThreadName();
    void setCurrentThreadName(const std::string &);
    void setCurrentThreadId(const std::thread::id &);
}

#endif
