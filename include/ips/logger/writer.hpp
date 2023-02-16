#ifndef IPSLOGGER_WRITER_HPP
#define IPSLOGGER_WRITER_HPP

#include <iosfwd>

namespace ips::logger
{
    class Writer {
    public:
        virtual ~Writer() = 0;

        virtual void write(const std::string& data) = 0;
    };
}

#endif /* IPSLOGGER_WRITER_HPP */
