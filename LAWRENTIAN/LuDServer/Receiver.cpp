#include "Receiver.h"
#include "FileSystem.h"
#include "FileSystemI.h"

using namespace FileSystem;

Receiver::Receiver()
{
    ic = Ice::initialize();
    Ice::ObjectAdapterPtr adapter
            = ic->createObjectAdapterWithEndpoints("FileSystem","default -p 10000");
    FilePtr file = new FileSystemI;
    adapter->add(file,ic->stringToIdentity("FileSystem"));
    adapter->activate();
    ic->waitForShutdown();
}

Receiver::Receiver(bool b)
{
    ic = Ice::initialize();
    Ice::ObjectAdapterPtr adapter
            = ic->createObjectAdapterWithEndpoints("FileSystem","default -p 10000");
    FilePtr file = new FileSystemI;
    adapter->add(file,ic->stringToIdentity("FileSystem"));
    if(b)
    {
        adapter->activate();
        ic->waitForShutdown();
    }
}
