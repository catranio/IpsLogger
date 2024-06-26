#include "streamWriter.hpp"

#include <ostream>

namespace ips::logger::details {

StreamWriter::StreamWriter(std::ostream& os) : os_(os) {}

void StreamWriter::write(const std::string_view data) noexcept { os_ << data; }

}  // namespace ips::logger::details
