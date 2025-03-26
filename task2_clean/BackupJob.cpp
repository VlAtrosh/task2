#include "BackupJob.h"

void BackupJob::addFile(const std::string& filePath) {
    files_.emplace_back(filePath);
}

void BackupJob::runBackup(const std::string& outputPath, bool splitMode) {
    if (files_.empty()) {
        throw std::logic_error("No files to backup");
    }

    if (splitMode) {
        for (const auto& file : files_) {
            storage_.saveSplit(file, outputPath);
        }
    }
    else {
        storage_.saveSingle(files_, outputPath + "/backup_full.bin");
    }
}