#include "BackupJob.h"
#include <iostream>

int main() {
    try {
        BackupJob job;

        job.addFile("documents/report.docx");
        job.addFile("images/photo.jpg");

        job.runBackup("backups", true);

        std::cout << "Backup completed successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Backup failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}