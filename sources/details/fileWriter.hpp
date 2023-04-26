#ifndef IPSLOGGER_DETAILS_FILEWRITER_HPP
#define IPSLOGGER_DETAILS_FILEWRITER_HPP

#include <ips/logger/writer.hpp>

#include <string>
#include <fstream>

namespace ips::logger::details
{
	class FileWriter : public Writer {
    public:
        explicit FileWriter(std::string_view filename, unsigned rotateInterval = 0);

        ~FileWriter() override;

        void write(std::string_view data) noexcept final;

    private:
        void rotate() noexcept;

        bool open(std::string_view filename) noexcept;

        constexpr std::string_view rotateFormat() const noexcept;

    private:
        using seconds_t = time_t;
        std::ofstream file_;
        std::string filename_;
        seconds_t intervalRotate_;
    };
}

#endif /* IPSLOGGER_DETAILS_FILEWRITER_HPP */
