#ifndef IPSLOGGER_FORMATTER_HPP
#define IPSLOGGER_FORMATTER_HPP

#include <iosfwd>

namespace ips::logger
{
    class Recorder;

    class Formatter {
    public:
        virtual ~Formatter() = default;

        [[nodiscard]] virtual std::string fmt(const Recorder& recorder) const noexcept = 0;
    };
}

#endif /* IPSLOGGER_FORMATTER_HPP */
