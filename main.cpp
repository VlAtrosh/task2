#include "BackupSystem.h"

int main() {
    BackupJob backupJob;
    backupJob.setStorage(std::make_unique<FileStorage>());
    backupJob.setBackupAlgorithm(std::make_unique<SplitStorage>());

    backupJob.addBackupObject(BackupObject("file1.txt", "File 1"));
    backupJob.addBackupObject(BackupObject("file2.txt", "File 2"));
    backupJob.createRestorePoint();

    backupJob.runBackup();

    return 0;
}