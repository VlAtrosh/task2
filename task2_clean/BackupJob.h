#pragma once
#include "FileBackupObject.h"
#include "LocalStorage.h"
#include <vector>
#include <memory>

class BackupJob {
public:
    void addFile(const std::string& filePath);
    void runBackup(const std::string& outputPath, bool splitMode);

private:
    std::vector<FileBackupObject> files_;
    LocalStorage storage_;
};