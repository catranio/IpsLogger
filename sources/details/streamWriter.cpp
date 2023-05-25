#include "streamWriter.hpp"

#include <ostream>

using namespace ips::logger::details;

StreamWriter::StreamWriter(std::ostream& os) : os_(os) {}

void StreamWriter::write(std::string_view data) noexcept { os_ << data; }

StreamWriter::~StreamWriter() {}