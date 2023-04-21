#ifndef IPSLOGGER_DETAILS_DATEFORMATTER_HPP
#define IPSLOGGER_DETAILS_DATEFORMATTER_HPP

#include <ips/logger/formatter.hpp>

namespace ips::logger::details
{
    class DateFormatter : public Formatter {
    public:
        [[nodiscard]] std::string fmt(const Recorder& recorder) const noexcept;
    };
}

#endif /* IPSLOGGER_DETAILS_DATEFORMATTER_HPP */
