#ifndef IPSLOGGER_WRITER_HPP
#define IPSLOGGER_WRITER_HPP

#include <string_view>

namespace ips::logger {
    class Writer {
    public:
        virtual ~Writer() = default;

        virtual void write(std::string_view data) = 0;
    };
}

#endif /* IPSLOGGER_WRITER_HPP */
