/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-06 16:22:27
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-06 22:21:34
 * @Description: ipv4 socket
 */
#include<arpa/inet.h>
#include<memory>
namespace Itachi{
    using socket_unique_ptr=std::unique_ptr<Socket>;
    using socket_shared_ptr=std::shared_ptr<Socket>;
    using sockaddr_shared_ptr=std::shared_ptr<struct  sockaddr_in>;
    using sockaddr_unique_ptr=std::unique_ptr<struct  sockaddr_in>;
    class Socket{
    public:
        Socket(){
            
        }
        ~Socket(){

        }
        ssize_t read();
        ssize_t readv();
        ssize_t readFrom();
        ssize_t sendTo();
        int send();
        void setTcpNoDelay();
        void setSendTimeOut();
        void setRecvTieOut();
        void setRecvBuffer();
        void setSendBuffer();
        void setConnectTimeOut();
    private:
        int  m_fd;
        sockaddr_unique_ptr m_locaaddr;
        sockaddr_unique_ptr m_peeraddr;
    };
}