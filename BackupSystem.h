#ifndef BACKUPSYSTEM_H
#define BACKUPSYSTEM_H

#include <string>
#include <vector>
#include <memory>
#include <ctime>
#include <stdexcept>
#include <iostream>


class BackupObject {
public:
    BackupObject(const std::string& path, const std::string& name);
    std::string getPath() const;
    std::string getName() const;

private:
    std::string path;
    std::string name;
};


class RestorePoint {
public:
    void addBackupObject(const BackupObject& object);
    std::vector<BackupObject> getBackupObjects() const;
    std::time_t getTimestamp() const;
    RestorePoint();

private:
    std::vector<BackupObject> backupObjects;
    std::time_t timestamp;
};


class Storage {
public:
    virtual void save(const std::vector<BackupObject>& objects, const std::string& path) = 0;
    virtual ~Storage() = default;
};

class BackupAlgorithm {
public:
    virtual void backup(const std::vector<BackupObject>& objects, Storage& storage) = 0;
    virtual ~BackupAlgorithm() = default;
};

class SplitStorage : public BackupAlgorithm {
public:
    void backup(const std::vector<BackupObject>& objects, Storage& storage) override;
};

class SingleStorage : public BackupAlgorithm {
public:
    void backup(const std::vector<BackupObject>& objects, Storage& storage) override;
};

class BackupJob {
public:
    void addBackupObject(const BackupObject& object);
    void createRestorePoint();
    void setBackupAlgorithm(std::unique_ptr<BackupAlgorithm> algorithm);
    void setStorage(std::unique_ptr<Storage> storage);
    void runBackup();

private:
    std::vector<RestorePoint> restorePoints;
    std::unique_ptr<RestorePoint> currentRestorePoint;
    std::unique_ptr<BackupAlgorithm> backupAlgorithm;
    std::unique_ptr<Storage> storage;
};

class FileStorage : public Storage {
public:
    void save(const std::vector<BackupObject>& objects, const std::string& path) override;
};

#endif 