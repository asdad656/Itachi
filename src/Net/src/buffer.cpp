/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-06 15:49:14
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-07 11:18:03
 * @Description: 
 */
#include"buffer.h"
#include<sys/socket.h>
#include<sys/uio.h>
namespace Itachi{
    ssize_t Buffer::readFromFd(int fd,int*saveError){
        size_t writeableByte=writeableBuffer();
        char extrBuf[65536];
        iovec buffers[2];
        buffers[0].iov_base=beginWrite();
        buffers[0].iov_len=writeableByte;
        buffers[1].iov_base=extrBuf;
        buffers[1].iov_len=sizeof(extrBuf);
        short buffer_count=writeableByte>=sizeof(extrBuf)?1:2;
        ssize_t n=readv(fd,buffers,buffer_count);
        if(n<0){
            *saveError=errno;
            return 0;
        }else if(n<=writeableByte){
            hasWriten(n);
        }else{
            hasWriten(writeableByte);
            n=n-writeableByte;
            write(extrBuf,n);
        }
        return n;
    }
}