#ifndef IPSLOGGER_DETAILS_FILEWRITER_HPP
#define IPSLOGGER_DETAILS_FILEWRITER_HPP

#include <ips/logger/writer.hpp>

#include <memory>

namespace ips::logger::details
{
    class FileWriter : public Writer {
    public:
        explicit FileWriter(std::string_view name);
        ~FileWriter() override;

        void write(std::string_view data) noexcept final;

    private:
        std::unique_ptr<std::ofstream> file_;
    };
}

#endif /* IPSLOGGER_DETAILS_FILEWRITER_HPP */
