#ifndef IPSLOGGER_DETAILS_DATEFORMATTER_HPP
#define IPSLOGGER_DETAILS_DATEFORMATTER_HPP

#include <ips/logger/formatter.hpp>

namespace ips::logger::details {
class DateFormatter : public Formatter {
 public:
  void fmt(const Recorder& recorder, std::string& dest) const noexcept override;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_DATEFORMATTER_HPP */
