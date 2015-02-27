#ifndef FILESYSTEMI_H
#define FILESYSTEMI_H

#include <Ice/Ice.h>
#include "FileSystem.h"
#include <Windows.h>

struct Time_t{
    std::string dayOfTheWeek;
    std::string day;
    std::string month;
    std::string year;
    std::string hour;
    std::string minute;
    std::string second;
    std::string milliseconds;
};

class FileSystemI : public FileSystem::File
{
private:
    std::string COPY;
    std::string IMAGE;
    bool getCreationTime(const std::string& path, FileSystem::TimeIce& time);
    std::string main_dir;
    bool dirExists(const std::string& dirName_in);
    std::string extractFileName(const std::string& str);
    std::string extractNodeName(const std::string str);
    std::string insertCorrectly(const std::string& str, const char* num);
    std::string getIP(const Ice::Current& c);
    void consolePrint(const std::string& str);
    std::string getName(const std::string& ip_address);
    std::string getfName(const std::string& s);
    std::string fixExtension(const std::string& s, const std::string& type);
    bool deleteDirectory(const std::string& dir, int len, bool noRecycleBin);

public:
    FileSystemI(std::string main_node);
    FileSystemI();

    virtual FileSystem::ByteSeq
    receiveLatest(const std::string& sec, const std::string& art,
                  const std::string& type, const std::string& fName,
                  const Ice::Current& c);

    virtual FileSystem::ByteSeq
    receiveVersion(const std::string& sec, const std::string& art,
                   const std::string& type, const std::string& fName,
                   const int ver, const Ice::Current& c);

    virtual bool
    sendFile(const std::string& sec, const std::string& art,
             const std::string& type, const std::string& fNameExt,
             const FileSystem::ByteSeq& seq, const Ice::Current& c);

    virtual FileSystem::VerSeq
    getHistory(const std::string& sec, const std::string& art,
             const std::string& type, const std::string& fName,
             const Ice::Current& c);

    virtual bool
    changeDir(const std::string& sec, const std::string& art_old,
              const std::string& art_new, const Ice::Current& c);

    virtual bool
    deleteArt(const std::string& sec, const std::string& art, const Ice::Current& c);

};

#endif // FILESYSTEMI_H
