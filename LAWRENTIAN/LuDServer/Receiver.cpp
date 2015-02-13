#include "Receiver.h"
#include "FileSystem.h"
#include "FileSystemI.h"

using namespace FileSystem;

static const std::string connection = "tcp -h 143.44.10.35 -p 10001";

Receiver::Receiver(const std::string& path)
{
    ic = Ice::initialize();
    Ice::ObjectAdapterPtr adapter
            = ic->createObjectAdapterWithEndpoints("FileSystem",connection);
    FilePtr file = path.size() ? new FileSystemI(path) : new FileSystemI();
    adapter->add(file,ic->stringToIdentity("FileSystem"));
    adapter->activate();
    ic->waitForShutdown();
}

Receiver::Receiver(const std::string& con, const std::string& path)
{
    ic = Ice::initialize();
    Ice::ObjectAdapterPtr adapter
            = ic->createObjectAdapterWithEndpoints("FileSystem",con);
    FilePtr file = path.size() ? new FileSystemI(path) : new FileSystemI();
    adapter->add(file,ic->stringToIdentity("FileSystem"));
    adapter->activate();
    ic->waitForShutdown();
}

Receiver::Receiver(const int& num, const std::string& path)
{
    ic = Ice::initialize();
    Ice::ObjectAdapterPtr adapter
            = num ? ic->createObjectAdapterWithEndpoints("FileSystem",connection) : ic->createObjectAdapterWithEndpoints("FileSystem","default -p 10000");
    FilePtr file = path.size() ? new FileSystemI(path) : new FileSystemI();
    adapter->add(file,ic->stringToIdentity("FileSystem"));
    adapter->activate();
    ic->waitForShutdown();
}
