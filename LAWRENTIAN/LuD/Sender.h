#ifndef SENDER_H
#define SENDER_H

#include <Ice/Ice.h>
#include "FileSystem.h"
#include <fstream>
#include <string>

class Sender
{
    Ice::CommunicatorPtr ic;
    FileSystem::FilePrx fpx;
public:
    Sender();
    Sender(const std::string& connection);
    Sender(const int& num);
    ~Sender();
    bool sendFile(const std::string& issueDate, const std::string& sec, const std::string& art, const std::string& type, const std::string& fName, const std::string& clDir);
    bool requestFile(const std::string& issueDate, const std::string& sec, const std::string& art, const std::string& type, const std::string& fName, const std::string& down_dir, int ver = -1);
    FileSystem::VerSeq getHistory(const std::string& issueDate, const std::string& sec, const std::string& art, const std::string& type, const std::string& fName);
    FileSystem::StrSeq getImageList(const std::string& issueDate, const std::string& sec, const std::string& art);
    bool changeDir(const std::string& issueDate,const std::string& sec, const std::string& artOld, const std::string& artNew);
    bool moveArtToSection(const std::string& issueDate,const std::string& secOld, const std::string& secNew, const std::string& art);
    bool archiveIssue(const std::string& issueDate);
    bool deleteArt(const std::string& issueDate,const std::string& sec, const std::string& art);
    bool deleteAllImages(const std::string& issueDate,const std::string& sec, const std::string& art);
    bool deleteImage(const std::string& issueDate,const std::string& sec, const std::string& art, const std::string& name);
    bool deleteAllCopies(const std::string& issueDate, const std::string& sec, const std::string& art);
    bool deleteCopyVer(const std::string& issueDate,const std::string& sec, const std::string art, int ver = -1);

};

#endif // SENDER_H
