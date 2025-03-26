#include "FileBackupObject.h"
#include <fstream>
#include <stdexcept>

FileBackupObject::FileBackupObject(const std::string& filePath)
    : filePath_(filePath) {
    if (!exists()) {
        throw std::runtime_error("File not found: " + filePath_.string());
    }
}

std::vector<uint8_t> FileBackupObject::readData() const {
    std::ifstream file(filePath_, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filePath_.string());
    }

    const auto fileSize = static_cast<size_t>(file.tellg());
    file.seekg(0);

    std::vector<uint8_t> buffer(fileSize);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
        throw std::runtime_error("Failed to read file: " + filePath_.string());
    }

    return buffer;
}

bool FileBackupObject::exists() const {
    return std::filesystem::exists(filePath_);
}