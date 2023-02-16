#ifndef IPSLOGGER_DATEFORMATTER_HPP
#define IPSLOGGER_DATEFORMATTER_HPP

#include <ips/logger/formatter.hpp>

namespace ips::logger
{
    class DateFormatter : public Formatter {
    public:
        virtual std::string fmt(const Recorder& recorder) noexcept override final;
    };
}

#endif /* IPSLOGGER_DATEFORMATTER_HPP */
