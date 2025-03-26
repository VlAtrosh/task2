#pragma once
#include "FileBackupObject.h"
#include <vector>
#include <string>

class LocalStorage {
public:
    void saveSingle(const std::vector<FileBackupObject>& files,
        const std::string& outputPath);
    void saveSplit(const FileBackupObject& file,
        const std::string& outputDir);
};