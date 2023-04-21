#ifndef IPSLOGGER_DETAILS_STREAMWRITER_HPP
#define IPSLOGGER_DETAILS_STREAMWRITER_HPP

#include <ips/logger/writer.hpp>

#include <iosfwd>

namespace ips::logger::details
{
	class StreamWriter : public Writer {
	public:
		explicit StreamWriter(std::ostream& os);
		~StreamWriter() override;

		void write(std::string_view data) noexcept final;

	private:
		std::ostream& os_;
	};
}

#endif /* IPSLOGGER_DETAILS_STREAMWRITER_HPP */
