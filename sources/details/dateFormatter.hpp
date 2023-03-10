#ifndef IPSLOGGER_DETAILS_DATEFORMATTER_HPP
#define IPSLOGGER_DETAILS_DATEFORMATTER_HPP

#include "ips/logger/formatter.hpp"
#include "ips/logger/definitions.hpp"

#include <string_view>

namespace ips::logger::details
{
    class DateFormatter : public Formatter {
    public:
        std::string fmt(const Recorder& recorder) noexcept final;

    private:
        constexpr static std::string_view to_string(Severity severity) noexcept;
    };
}

#endif /* IPSLOGGER_DETAILS_DATEFORMATTER_HPP */
