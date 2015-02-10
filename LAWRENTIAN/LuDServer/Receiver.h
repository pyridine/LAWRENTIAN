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
    Receiver();
    Receiver(bool b);
};

#endif // RECEIVER_H
