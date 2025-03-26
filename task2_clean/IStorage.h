#include "FileBackupObject.h"
#include <fstream>
#include <stdexcept>
#include <iterator>

FileBackupObject::FileBackupObject(const std::string& filePath)
    : filePath_(filePath) {
    if (filePath.empty()) {
        throw std::invalid_argument("File path cannot be empty");
    }
}

std::string FileBackupObject::getPath() const {
    return filePath_;
}

std::vector<uint8_t> FileBackupObject::getData() const {
    std::ifstream file(filePath_, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath_);
    }

    return { std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>() };
}