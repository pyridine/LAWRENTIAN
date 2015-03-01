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
    Receiver(const std::string& main_dir  = "C:/Users/Briggs 419 Server/Dropbox/Issue", const std::string& arc_dir = "C:/Users/Briggs 419 Server/Dropbox/Archive");
    Receiver(const int& num, const std::string& con, const std::string& main_dir, const std::string& arc_dir);
    Receiver(const int& num, const std::string& main_dir  = "C:/Programs/Issue", const std::string& arc_dir = "C:/Programs/Archive");
};

#endif // RECEIVER_H
