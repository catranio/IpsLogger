#ifndef IPSLOGGER_DETAILS_CONSOLEFROMATTER_HPP
#define IPSLOGGER_DETAILS_CONSOLEFROMATTER_HPP

#include "dateFormatter.hpp"

namespace ips::logger::details {
class ConsoleFormatter : public DateFormatter {
 public:
  [[nodiscard]] std::string fmt(const Recorder& recorder) const noexcept;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_CONSOLEFROMATTER_HPP */
