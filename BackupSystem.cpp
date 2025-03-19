#include "BackupSystem.h"

BackupObject::BackupObject(const std::string& path, const std::string& name)
    : path(path), name(name) {}

std::string BackupObject::getPath() const {
    return path;
}

std::string BackupObject::getName() const {
    return name;
}

RestorePoint::RestorePoint() : timestamp(std::time(nullptr)) {}

void RestorePoint::addBackupObject(const BackupObject& object) {
    backupObjects.push_back(object);
}

std::vector<BackupObject> RestorePoint::getBackupObjects() const {
    return backupObjects;
}

std::time_t RestorePoint::getTimestamp() const {
    return timestamp;
}

void SplitStorage::backup(const std::vector<BackupObject>& objects, Storage& storage) {
    for (const auto& obj : objects) {
        storage.save({obj}, obj.getPath());
    }
}

void SingleStorage::backup(const std::vector<BackupObject>& objects, Storage& storage) {
    storage.save(objects, "backup_archive.zip");
}

void BackupJob::addBackupObject(const BackupObject& object) {
    if (!currentRestorePoint) {
        currentRestorePoint = std::make_unique<RestorePoint>();
    }
    currentRestorePoint->addBackupObject(object);
}

void BackupJob::createRestorePoint() {
    if (currentRestorePoint) {
        restorePoints.push_back(*currentRestorePoint);
        currentRestorePoint.reset();
    }
}

void BackupJob::setBackupAlgorithm(std::unique_ptr<BackupAlgorithm> algorithm) {
    backupAlgorithm = std::move(algorithm);
}

void BackupJob::setStorage(std::unique_ptr<Storage> storage) {
    this->storage = std::move(storage);
}

void BackupJob::runBackup() {
    if (!backupAlgorithm || !storage) {
        throw std::runtime_error("Backup algorithm or storage not set");
    }

    for (const auto& restorePoint : restorePoints) {
        backupAlgorithm->backup(restorePoint.getBackupObjects(), *storage);
    }
}

void FileStorage::save(const std::vector<BackupObject>& objects, const std::string& path) {
    std::cout << "Saving " << objects.size() << " objects to " << path << std::endl;
}