/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-06 16:22:27
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 12:56:37
 * @Description: ipv4 socket
 */
#include<arpa/inet.h>
#include<memory>
namespace Itachi{
    class Socket;
    using socket_unique_ptr=std::unique_ptr<Socket>;
    using socket_shared_ptr=std::shared_ptr<Socket>;
    using sockaddr_shared_ptr=std::shared_ptr<struct  sockaddr_in>;
    using sockaddr_unique_ptr=std::unique_ptr<struct  sockaddr_in>;
    class Socket{
    public:
        Socket(){
            
        }


        Socket(int fd,sockaddr_in*peeraddr,sockaddr_in*localaddr):
        m_fd(fd),
        m_peeraddr(peeraddr),
        m_locaaddr(localaddr)
        {
            
        }
        ~Socket(){

        }
        void setReuseAddr(const bool &);
        void setReusePort(const bool &);
        void setTcpKeepAlive(const bool &);
        void setNoBlock(const bool &);
        void setTcpNoDelay(const bool &);
        void setSendTimeOut(const int&);
        void setRecvTieOut(const int&);
        void setRecvBuffer(const int &);
        void setSendBuffer(const int &);
        void setConnectTimeOut(const int &);
        int getFd()const noexcept{
            return m_fd;
        }
        const sockaddr_in*getPeerAddr()noexcept{
            return m_peeraddr.get();
        }
        const sockaddr_in*getLocalAddr()noexcept{
            return m_locaaddr.get();
        }
    private:
        int  m_fd;
        sockaddr_unique_ptr m_locaaddr;
        sockaddr_unique_ptr m_peeraddr;
    };
}