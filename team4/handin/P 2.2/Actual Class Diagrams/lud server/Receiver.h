#ifndef RECEIVER_H
#define RECEIVER_H

#include <Ice/Ice.h>
#include "FileSystem.h"
#include <fstream>
#include <string>

class Receiver
{
    Ice::CommunicatorPtr ic;
    FileSystem::FilePrx fpx;
public:
    Receiver(const std::string path  = "C:/Users/Briggs 419 Server/Dropbox/Issue");
    Receiver(const int& num, const std::string& con, const std::string path);
    Receiver(const int& num, const std::string path = "C:/Programs");
};

#endif // RECEIVER_H
