/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-09 11:28:01
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 20:27:40
 * @Description: H
 */
#include "tcpConnection.h"
#include <arpa/inet.h>
#include "EventLoop.h"
#include "buffer.h"
#include "socket.h"
#include "channel.h"
#include <sys/socket.h>
#include <fcntl.h>
#include "sstream"
#include <functional>
#include <unistd.h>
#include "adaptor.h"
namespace Itachi
{
    TcpConnection::TcpConnection(EventLoop *ownerLoop,
                                 int fd,
                                 sockaddr_in *peerAddr,
                                 const sockaddr_in *localaddr,
                                 const std::string&name):
    m_state(State::NEW),
    m_socket(new Socket(fd,peerAddr,new sockaddr_in(*localaddr))),
    m_ownerLoop(ownerLoop),
    m_outPutBuffer(new Buffer),
    m_inPutBuffer(new Buffer),
    m_channel(new Channel(m_ownerLoop, fd)),
    m_name(name)
{
        m_channel->setCloseCallBack(
            std::bind(&TcpConnection::handleClose, this));

        m_channel->setErrorCallBack(
            std::bind(&TcpConnection::handleClose, this));
        m_channel->setReadCallback(
            std::bind(&TcpConnection::handleMessage, this));
        m_channel->setWriteCallBack(
            std::bind(&TcpConnection::handleWrite, this));
        m_ownerLoop->runInLoop(
            std::bind(&TcpConnection::connectionEntablish,this)
        );
    }
    TcpConnection::~TcpConnection()
    {
        m_state = State::DESTORY;
    }
    void TcpConnection::connectionEntablish(){
        assert(m_ownerLoop->isInLoopThread());
        LOG_DEBUG<<"   "<<m_name<<"   connectionEntablish!!!";
        m_channel->enableRead();
        if(m_ConnectionCallBack){
            m_ConnectionCallBack(shared_from_this(),0);
        }
    }

    void TcpConnection::connectionDestory(){
                m_channel->disableAll();
                m_ownerLoop->removeChannel(m_channel.get());
    }
    //-------------------------------get------------------------------------------//
    int TcpConnection::getFd() const
    {
        return m_socket->getFd();
    }
    const sockaddr_in *TcpConnection::getLocalAddr() const
    {
        return m_socket->getLocalAddr();
    }
    const sockaddr_in *TcpConnection::getPeerAddr() const
    {
        return m_socket->getPeerAddr();
    }
    TcpConnection::State TcpConnection::getTcpState() const
    {
        return m_state;
    }
    //-------------------------------set------------------------------------------//
    void TcpConnection::setConnectionCallBack(TcpConnectionCallBack cb)
    {
        m_ConnectionCallBack = std::move(cb);
    }
    void TcpConnection::setCloseCallBack(TcpCloseCallBack cb)
    {
        m_CloseCallBack = std::move(cb);
    }
    void TcpConnection::setErrorCallBack(TcpErrorCallBack cb)
    {
        m_ErrorCallBack = std::move(cb);
    }
    void TcpConnection::setMessageCallBack(TcpMessaageCallBack cb)
    {
        m_messageCallBack = std::move(cb);
    }
    void TcpConnection::setTcpState(const State &state)
    {
        m_state = state;
    }
    std::string TcpConnection::toString() const
    {
        std::stringstream oss;
        dump(oss);
        return oss.str();
    }
    std::ostream &TcpConnection::dump(std::ostream &os) const
    {
        os << m_socket->toString();
    }
    //-------------------------------opt------------------------------------------//
    void TcpConnection::handleMessage()
    {
        int  saveerror;
        ssize_t n=m_inPutBuffer->readFromFd(m_socket->getFd(),&saveerror);
        if(n==0){
            handleClose();
        }
        if(n<0)
        {
            LOG_FATAL<<"handleMessage failed!!   error is "<<saveerror;
        }
        if(m_messageCallBack)
        m_messageCallBack(shared_from_this(), m_inPutBuffer.get(), 0);
    }
    void TcpConnection::handleClose()
    {
        if(m_CloseCallBack)
        m_CloseCallBack(shared_from_this(), 0);
    }
    void TcpConnection::handleError()
    {
        if(m_ErrorCallBack)
        m_ErrorCallBack(shared_from_this(), 0);
    }
    void TcpConnection::handleWrite()
    {
        if (m_channel->isableWrite())
        {
            ssize_t n = ::write(m_socket->getFd(), m_outPutBuffer->beginRead(), m_outPutBuffer->readableBuffer());
            if (n < 0)
            {
                LOG_ERROR << "write faild!!";
            }
            else if (n > 0)
            {
                if (n == m_outPutBuffer->readableBuffer())
                {
                    m_channel->disableWrite();
                }
                m_outPutBuffer->hasRead(n);
            }
        }
    }

    void TcpConnection::sendInLoop(const void *buffer, size_t len)
    {
        size_t resume = len;
        if (!m_channel->isableWrite() && m_outPutBuffer->readableBuffer() == 0)
        {
            ssize_t n = write(m_socket->getFd(), buffer, len);
            if (n < 0)
            {
                LOG_ERROR << "write faild!!";
            }
            resume -= n;
        }
        ASSERT(resume <= len);
        if (resume > 0)
        {
            m_outPutBuffer->write(buffer + len - resume, resume);
            if (!m_channel->isableWrite())
            {
                m_channel->enableWrite();
            }
        }
    }
    void TcpConnection::send(const std::string &str)
    {
        this->send(str.c_str(), str.size() + 1);
    }
    void TcpConnection::send(const void *buffer, size_t len)
    {
        if (m_ownerLoop->isInLoopThread())
        {
            sendInLoop(buffer, len);
        }
        else
        {
            m_ownerLoop->runInLoop(std::bind(
                &TcpConnection::sendInLoop, this, buffer, len));
        }
    }
    void TcpConnection::send(Buffer *buffer, size_t len)
    {
        this->send(buffer->beginRead(), len);
        buffer->hasRead(len);
    }

}