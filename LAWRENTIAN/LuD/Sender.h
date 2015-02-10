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
    ~Sender();
    bool sendFile(const std::string& dir_sf, const std::string& name);
    bool requestFile(const std::string& dir_rf, const std::string& down_dir);
};

#endif // SENDER_H
