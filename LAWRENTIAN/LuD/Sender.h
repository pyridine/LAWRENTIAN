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
    void sendFile(std::string, std::vector<std::string>);
    std::ofstream requestFile(std::string, std::vector<std::string>*);
};

#endif // SENDER_H
