/*
 * @Author: lqf
 * @page: www.Jackey.top
 * @Date: 2022-03-06 15:49:08
 * @LastEditors: lqf
 * @LastEditTime: 2022-03-11 11:00:06
 * @Description: 缓冲类
 */
#ifndef __BUFFER__H__
#define __BUFFER__H__
#include <vector>
#include <memory>
#include <string.h>
#include "definition.h"
namespace Itachi
{
    static const char*CRLF="\r\n";
    static constexpr size_t preReserveBufferSize = 8;
    static constexpr size_t defaultBufferSize = 4096;
    class Buffer;
    using buffer_shared_ptr = std::shared_ptr<Buffer>;
    class Buffer
    {
    public:
        Buffer(const size_t &BuffeSize = defaultBufferSize,
               const size_t &preReserveBufferSize = preReserveBufferSize) : m_buffer(BuffeSize),
                                                                            m_readable_Index(preReserveBufferSize),
                                                                            m_writeable_Index(preReserveBufferSize),
                                                                            m_preReserve_index(preReserveBufferSize)
        {
            ASSERT(readableBuffer() == 0);
        }

        size_t readableBuffer() const
        {
            return m_writeable_Index - m_readable_Index;
        }

        size_t writeableBuffer() const
        {
            return m_buffer.size() - m_writeable_Index;
        }

        size_t preReserveBuffer() const
        {
            return m_preReserve_index;
        }

        size_t preVacateBuffer() const
        {
            return m_readable_Index - m_preReserve_index;
        }

        size_t maxBufferSIze() const
        {
            return m_buffer.size();
        }

        size_t maxWriteaableSIze() const
        {
            return m_buffer.size() - m_writeable_Index;
        }

        const char *begin() const
        {
            return &m_buffer[0];
        }

        char *begin()
        {
            return &m_buffer[0];
        }

        char *beginRead()
        {
            return &m_buffer[m_readable_Index];
        }

        const char *beginRead() const
        {
            return &m_buffer[m_readable_Index];
        }

        const char *beginWrite() const
        {
            return &m_buffer[m_writeable_Index];
        }

        char *beginWrite()
        {
            return &m_buffer[m_writeable_Index];
        }

        // const char *beginWrite() const
        // {
        //     return &m_buffer[m_writeable_Index];
        // }

        void hasWriten(const size_t &len)
        {
            ASSERT(len <= writeableBuffer());
            m_writeable_Index += len;
        }

        void hasRead(const size_t &len)
        {
            ASSERT(len <= readableBuffer());
            m_readable_Index += len;
        }

        void enSureSIze(const size_t &len)
        {
            if (writeableBuffer() >= len)
                return;

            autoFill(len);
        }

        void autoFill(const size_t &len)
        {
            if (writeableBuffer() >= len)
                return;

            if (len + m_preReserve_index > writeableBuffer() + preVacateBuffer())
            {
                m_buffer.resize(m_buffer.size() + ((len - writeableBuffer()) << 1));
            }
            else
            {
                size_t readable = readableBuffer();
                memcpy(
                    begin() + m_preReserve_index,
                    beginRead(),
                    readable);
                m_readable_Index = m_preReserve_index;
                m_writeable_Index = m_preReserve_index + readable;
                ASSERT(m_readable_Index <= m_writeable_Index);
                ASSERT(m_readable_Index == m_preReserve_index);
            }
            ASSERT(writeableBuffer() >= len);
        }

        void write(const void *src, const size_t &len)
        {
            enSureSIze(len);
            ASSERT(writeableBuffer() >= len);
            memcpy(beginWrite(),
                   src,
                   len);
            hasWriten(len);
        }

        void write(const std::string &src)
        {
            enSureSIze(src.size() + 1);
            ASSERT(writeableBuffer() >= src.size() + 1);
            memcpy(
                beginWrite(),
                src.c_str(),
                src.size() + 1);
            hasWriten(src.size() + 1);
        }

        std::string readAsString(const size_t &len)
        {
            ASSERT(len <= readableBuffer());
            if (len == readableBuffer())
            {
                return readAllAsString();
            }
            std::string str(beginRead(), len);
            hasRead(len);
            return str;
        }

        std::string readAllAsString()
        {
            ASSERT(readableBuffer() > 0);
            std::string str(beginRead(), readableBuffer());
            m_readable_Index = m_preReserve_index;
            m_writeable_Index = m_preReserve_index;
            return str;
        }

        const char *findEOF() const noexcept
        {
            const char *it = std::find(beginRead(), beginWrite(), '\r\n');
            return it == beginWrite() ? nullptr : it;
        }

        const char *FindEOF(const char *start) const noexcept
        {
            ASSERT(start >= beginRead() && start <= beginWrite());
            const char *it = std::find(start, beginWrite(), '\r\n');
            return it == beginWrite() ? nullptr : it;
        }

        const char *FindSpace() const noexcept
        {
            const char *it = std::find(beginRead(), beginWrite(), ' ');
            return it == beginWrite() ? nullptr : it;
        }

        const char *FindSpace(const char *start) const noexcept
        {
            ASSERT(start >= beginRead() && start <= beginWrite());
            const char *it = std::find(start, beginWrite(), ' ');
            return it == beginWrite() ? nullptr : it;
        }
        const char *findCRILF() const noexcept
        {
            auto it = std::search(beginRead(), beginWrite(), CRLF,CRLF+2);
            if (it != beginWrite())
            {
                return it;
            }
            return nullptr;
        }
        const char *findCRILF(const char *begin)
        {
            ASSERT(beginRead() <= begin && beginWrite()> begin);
            auto it = std::search(begin, (const char*)beginWrite(),CRLF,CRLF+2);
            if (it != beginWrite())
            {
                return it;
            }
            return nullptr;
        }

        void readAll(){
            m_readable_Index=m_writeable_Index=m_preReserve_index;
        }
        void readUntil(size_t index)
        {
            ASSERT(m_readable_Index <= index && m_writeable_Index >= index);
            m_readable_Index = index;
        }
        void readUntil(const char *index)
        {
            ASSERT(beginRead() <= index && beginWrite() >= index);
            if(index==beginWrite()){
                readAll();
            }else
            m_readable_Index = index - begin();
        }
        ssize_t readFromFd(int fd, int *saveError);

    private:
        std::vector<char> m_buffer;
        size_t m_readable_Index;
        size_t m_writeable_Index;
        size_t m_preReserve_index;
    };
}
#endif
