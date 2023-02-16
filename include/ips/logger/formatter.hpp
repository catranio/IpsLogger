#ifndef IPSLOGGER_FORMATTER_HPP
#define IPSLOGGER_FORMATTER_HPP

#include <iosfwd>

namespace ips::logger
{
    class Recorder;

    class Formatter {
    public:
        virtual ~Formatter() = 0;

        virtual std::string fmt(const Recorder& recorder) noexcept = 0;
    };
}

#endif /* IPSLOGGER_FORMATTER_HPP */
