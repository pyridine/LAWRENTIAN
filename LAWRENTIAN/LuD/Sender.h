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
    bool sendFile(const std::string& sec, const std::string& art, const std::string& type, const std::string& fNameExt, const std::string& clDir);
    bool requestFile(const std::string& sec, const std::string& art, const std::string& type, const std::string& fName, const std::string& down_dir, int ver = -1);
    FileSystem::VerSeq getHistory(const std::string& sec, const std::string& art, const std::string& type, const std::string& fName);
};

#endif // SENDER_H
