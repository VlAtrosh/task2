#include "LocalStorage.h"
#include <fstream>
#include <filesystem>

void LocalStorage::saveSingle(const std::vector<FileBackupObject>& files,
    const std::string& outputPath) {
    std::ofstream out(outputPath, std::ios::binary);
    if (!out) {
        throw std::runtime_error("Cannot create file: " + outputPath);
    }

    for (const auto& file : files) {
        auto data = file.readData();
        out.write(reinterpret_cast<const char*>(data.data()), data.size());
    }
}

void LocalStorage::saveSplit(const FileBackupObject& file,
    const std::string& outputDir) {
    const auto outputPath = std::filesystem::path(outputDir) / file.getPath().filename();
    std::ofstream out(outputPath, std::ios::binary);

    if (!out) {
        throw std::runtime_error("Cannot create file: " + outputPath.string());
    }

    auto data = file.readData();
    out.write(reinterpret_cast<const char*>(data.data()), data.size());
}