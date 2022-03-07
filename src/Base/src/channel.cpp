/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-07 18:46:22
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 19:30:15
 * @Description: 
 */
#include "channel.h"
#include <sys/epoll.h>
#include "definition.h"
namespace Itachi
{

    static const int K_READEVENT = EPOLLIN | EPOLLPRI;
    static const int K_WRITEEVENT = EPOLLOUT;
    static const int K_ERROREVENT = EPOLLERR;
    static const int K_NONEEVENT = 0;

    Channel::~Channel()
    {
        ASSERT(!m_isHandlingEvent);
    }

    void Channel::handle()
    {
        m_isHandlingEvent = true;
        //关闭
        if ((m_revent & EPOLLHUP) && !(m_revent && EPOLLIN))
        {
            if (m_closeCallBack)
            {
                LOG_INFO << "m_fd CLOSE ,m_closeCallBack is called";
                m_closeCallBack(m_fd);
            }
        }
        //可读
        if (m_revent & K_READEVENT)
        {
            if (m_readCallBack)
            {
                m_readCallBack(m_fd);
            }
        }
        //可写
        if (m_revent & K_WRITEEVENT)
        {
            if (m_writeCallback)
            {
                m_writeCallback(m_fd);
            }
        }
        //错误
        if (m_revent & K_ERROREVENT)
        {
            if (m_errorCallBack)
            {
                LOG_ERROR << "m_revent is K_ERROREVENT!!";
                m_errorCallBack(m_fd);
            }
        }
        m_isHandlingEvent = false;
    }
    void Channel::handleWrite()
    {
    }
    void Channel::handleRead()
    {
    }
    void Channel::handleClose()
    {
    }
    void Channel::enableRead()
    {
        m_event |= K_READEVENT;
        update();
    }
    void Channel::enableWrite()
    {
        m_event |= K_WRITEEVENT;
        update();
    }
    void Channel::update() const
    {
        //
    }
    void Channel::setRevent(const int &revent)
    {
        m_revent |= revent;
    }
    bool Channel::isableWrite() const
    {
        return m_event & K_WRITEEVENT;
    }
    bool Channel::isableRead() const
    {
        return m_event & K_READEVENT;
    }

    bool Channel::hasNoneEvent() const
    {
        return m_event == K_NONEEVENT;
    }

    void Channel::setReadCallback(const readableCallBack &cb)
    {
        m_readCallBack = cb;
    }
    void Channel::setReadCallback(readableCallBack &&cb)
    {
        m_readCallBack = std::move(cb);
    }
    void Channel::setWriteCallBack(const writeableCallBack &cb)
    {
        m_writeCallback = cb;
    }
    void Channel::setWriteCallBack(writeableCallBack &&cb)
    {
        m_writeCallback = cb;
    }
    void Channel::setCloseCallBack(const closeableCallBack &cb)
    {
        m_closeCallBack = cb;
    }
    void Channel::setCloseCallBack(closeableCallBack &&cb)
    {
        m_closeCallBack = cb;
    }
    void Channel::setErrorCallBack(const errorableCallBack &cb)
    {
        m_errorCallBack = cb;
    }
    void Channel::setErrorCallBack(errorableCallBack &&cb)
    {
        m_errorCallBack = cb;
    }

}