#include "fileWriter.hpp"

#include <fstream>

using namespace ips::logger::details;

FileWriter::FileWriter(const std::string& filename) : file_(std::make_unique<std::ofstream>()){
    file_->open(filename.data(), std::ios::out | std::ios::app);
    if (!file_->is_open()) {
        //todo: write what to do
    }
}

void FileWriter::write(const std::string& data) noexcept {
    file_->write(data.data(), static_cast<long>(data.size()));
}

FileWriter::~FileWriter() {
    file_->close();
}