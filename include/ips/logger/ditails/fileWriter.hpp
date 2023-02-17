#ifndef IPSLOGGER_FILEWRITER_HPP
#define IPSLOGGER_FILEWRITER_HPP

#include <ips/logger/writer.hpp>

#include <fstream>

namespace ips::logger::ditails
{
    class FileWriter : public Writer {
    public:
        explicit FileWriter(std::string_view name);
        ~FileWriter() override;

        void write(std::string_view data) noexcept final;

    private:
        std::ofstream file_;
    };
}

#endif /* IPSLOGGER_FILEWRITER_HPP */
