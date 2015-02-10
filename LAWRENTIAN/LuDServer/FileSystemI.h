#ifndef FILESYSTEMI_H
#define FILESYSTEMI_H

#include <Ice/Ice.h>
#include "FileSystem.h"

class FileSystemI : public FileSystem::File
{
private:
    std::string main_dir;
    virtual bool dirExists(const std::string& dirName_in);
    std::string extractName(const std::string& str);
    void FileSystemI::insertCorrectly(std::string& str, const char* num);
public:
    FileSystemI();
    FileSystemI(std::string main_node);

    virtual Ice::ByteSeq receiveFile(const std::string& path,
                                     const Ice::Current&);
    virtual bool sendFile(const std::string& str, const Ice::ByteSeq& seq,
                          const Ice::Current &);
};

#endif // FILESYSTEMI_H
