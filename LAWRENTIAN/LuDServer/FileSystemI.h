#ifndef FILESYSTEMI_H
#define FILESYSTEMI_H

#include <Ice/Ice.h>
#include "FileSystem.h"

class FileSystemI : public FileSystem::File
{
private:
    std::string main_dir;
    virtual bool dirExists(const std::string& dirName_in);
    std::string extractFileName(const std::string& str);
    std::string extractNodeName(const std::string str);
    std::string insertCorrectly(std::string& str, const char* num);
    std::string callerInfo(const Ice::Current& c);
    void consolePrint(const std::string& str);
public:
    FileSystemI(std::string main_node);
    FileSystemI();

    virtual Ice::ByteSeq receiveFile(const std::string& path,
                                     const Ice::Current& c);
    virtual bool sendFile(const std::string& str, const Ice::ByteSeq& seq,
                          const Ice::Current& c);
};

#endif // FILESYSTEMI_H
