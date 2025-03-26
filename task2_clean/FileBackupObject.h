#pragma once
#include <string>
#include <vector>
#include <filesystem>

class FileBackupObject {
public:
    explicit FileBackupObject(const std::string& filePath);
    std::string getPath() const;
    size_t getSize() const;
    std::vector<uint8_t> readData() const;
    bool exists() const;

private:
    std::filesystem::path filePath_;
};