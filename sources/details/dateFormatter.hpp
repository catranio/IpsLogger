#ifndef IPSLOGGER_DETAILS_DATEFORMATTER_HPP
#define IPSLOGGER_DETAILS_DATEFORMATTER_HPP

#include "ips/logger/formatter.hpp"
#include "ips/logger/definitions.hpp"

namespace ips::logger::details
{
    class DateFormatter : public Formatter {
    public:
        [[nodiscard]] std::string fmt(const Recorder& recorder) const noexcept final;
    };
}

#endif /* IPSLOGGER_DETAILS_DATEFORMATTER_HPP */
