/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-09 11:27:49
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-10 20:27:19
 * @Description: 
 */
#ifndef __TCPCONNECTION__H__
#define __TCPCONNECTION__H__
#include<string>
#include<ostream>
#include<memory>
#include"callback.h"
#include "noncopyaable.h"
struct sockaddr_in;
namespace Itachi
{
    class EventLoop;
    class Socket;
    class Buffer;
    class Channel;
    class TcpConnection : public nonCopyable,public std::enable_shared_from_this<TcpConnection>
    {
    public:
        using ptr=std::shared_ptr<TcpConnection>;
        enum class State{
            NEW,
            ENTABLISH,
            DESTORY
        };
        TcpConnection(EventLoop*,int,sockaddr_in*,const sockaddr_in*,const std::string&name="");
        ~TcpConnection();
        //-------------------------------get------------------------------------------//
        int getFd()const;
        const sockaddr_in*getLocalAddr()const;
        const sockaddr_in*getPeerAddr()const;
        State getTcpState()const;
        EventLoop*getLoop()const{return m_ownerLoop;}
        const std::string&getName()const{
            return m_name;
        }
        //-------------------------------set------------------------------------------//
        void setConnectionCallBack(TcpConnectionCallBack cb);
        void setCloseCallBack(TcpCloseCallBack cb);
        void setErrorCallBack(TcpErrorCallBack cb);
        void setMessageCallBack(TcpMessaageCallBack cb); 
        void setTcpState(const State&);
        std::string toString()const;
        std::ostream&dump(std::ostream&)const;
        //-------------------------------opt------------------------------------------//
        void connectionEntablish();
        void connectionDestory();
        void handleMessage();
        void handleClose();
        void handleError();
        void handleWrite();
        void sendInLoop(const void*,size_t);
        void send(const std::string&);
        void send(const void*,size_t len);
        void send(Buffer*,size_t len);
    private:
        State m_state;
        std::unique_ptr<Socket> m_socket;
        TcpConnectionCallBack m_ConnectionCallBack;
        TcpCloseCallBack m_CloseCallBack;
        TcpErrorCallBack m_ErrorCallBack;
        TcpMessaageCallBack m_messageCallBack;
        EventLoop*m_ownerLoop;
        std::unique_ptr<Buffer>m_outPutBuffer;
        std::unique_ptr<Buffer>m_inPutBuffer;
        std::unique_ptr<Channel>m_channel;
        std::string m_name;
    };
}

#endif
