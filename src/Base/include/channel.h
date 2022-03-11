/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 16:24:09
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 21:20:04
 * @Description: 
 */
#ifndef __CHANNEL___H__
#define __CHANNEL___H__
#include <functional>
#include <memory>
#include "callback.h"
#include "noncopyaable.h"
namespace Itachi
{
    class EventLoop;
    class Channel : public nonCopyable
    {
    public:
        Channel(EventLoop *eventloop, int fd) : m_ownerLoop(eventloop),
                                                m_fd(fd),
                                                m_isHandlingEvent(false),
                                                m_index(-1),
                                                m_event(0)
        {
        }
        ~Channel();
        void handle();
        void handleWrite();
        void handleRead();
        void handleClose();
        void enableRead();
        void enableWrite();
        void setRevent(const int &revent);
        bool isableWrite() const;
        bool isableRead() const;
        bool hasNoneEvent() const;
        void setReadCallback(const readableCallBack &);
        void setReadCallback(readableCallBack &&);
        void setWriteCallBack(const writeableCallBack &);
        void setWriteCallBack(writeableCallBack &&);
        void setCloseCallBack(const closeableCallBack &);
        void setCloseCallBack(closeableCallBack &&);
        void setErrorCallBack(const errorableCallBack &);
        void setErrorCallBack(errorableCallBack &&);
        void disableWrite();
         void disableAll();
        void setIndex(const int &index)
        {
            m_index = index;
        }

        int getFd() const
        {
            return m_fd;
        }
        int getIndex() const
        {
            return m_index;
        }
        int getEvent() const
        {
            return m_event;
        }
        int getRevent() const
        {
            return m_revent;
        }
        EventLoop *getOwnerLoop() const
        {
            return m_ownerLoop;
        }

    private:
        void update();

    private:
        int m_fd;
        int m_revent;
        int m_event;
        int m_index;
        readableCallBack m_readCallBack;
        writeableCallBack m_writeCallback;
        closeableCallBack m_closeCallBack;
        errorableCallBack m_errorCallBack;
        EventLoop *m_ownerLoop;
        bool m_isHandlingEvent = false;
    };
}

#endif