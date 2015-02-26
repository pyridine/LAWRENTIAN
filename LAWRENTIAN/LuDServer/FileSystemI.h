#ifndef FILESYSTEMI_H
#define FILESYSTEMI_H

#include <Ice/Ice.h>
#include "FileSystem.h"

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
    Time_t getCreationTime(const std::string& path);
    std::string main_dir;
    bool dirExists(const std::string& dirName_in);
    std::string extractFileName(const std::string& str);
    std::string extractNodeName(const std::string str);
    std::string insertCorrectly(std::string& str, const char* num);
    std::string getIP(const Ice::Current& c);
    void consolePrint(const std::string& str);
    std::string getName(const std::string& ip_address);
    std::string FileSystemI::getfName(const std::string& s);
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
};

#endif // FILESYSTEMI_H
