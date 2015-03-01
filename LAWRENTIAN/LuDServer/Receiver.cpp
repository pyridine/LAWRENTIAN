#include "Receiver.h"
#include "FileSystem.h"
#include "FileSystemI.h"

static const std::string connection = "tcp -h 143.44.10.35 -p 10001";
Receiver::Receiver(const std::string& main_dir, const std::string& arc_dir)
{
    using namespace FileSystem;

    ic = Ice::initialize();
    Ice::ObjectAdapterPtr adapter
            = ic->createObjectAdapterWithEndpoints("FileSystem",connection);
    FilePtr file = (main_dir.size() && arc_dir.size()) ? new FileSystemI(main_dir, arc_dir)
                                                       : new FileSystemI;
    adapter->add(file,ic->stringToIdentity("FileSystem"));
    adapter->activate();
    ic->waitForShutdown();
}

Receiver::Receiver(const int& num, const std::string& con, const std::string& main_dir, const std::string& arc_dir)
{
    using namespace FileSystem;
    using namespace std;
    cout << "actually an error: num must = 0" << endl;
    ic = Ice::initialize();
    Ice::ObjectAdapterPtr adapter
            = num ? ic->createObjectAdapterWithEndpoints("FileSystem",connection) : ic->createObjectAdapterWithEndpoints("FileSystem",con);
    FilePtr file = (main_dir.size() && arc_dir.size()) ? new FileSystemI(main_dir, arc_dir)
                                                       : new FileSystemI;
    adapter->add(file,ic->stringToIdentity("FileSystem"));
    adapter->activate();
    ic->waitForShutdown();
}

Receiver::Receiver(const int& num, const std::string& main_dir, const std::string& arc_dir)
{
    using namespace FileSystem;

    ic = Ice::initialize();
    Ice::ObjectAdapterPtr adapter
            = num ? ic->createObjectAdapterWithEndpoints("FileSystem",connection) : ic->createObjectAdapterWithEndpoints("FileSystem","default -p 10000");
    FilePtr file = (main_dir.size() && arc_dir.size()) ? new FileSystemI(main_dir, arc_dir)
                                                       : new FileSystemI;
    adapter->add(file,ic->stringToIdentity("FileSystem"));
    adapter->activate();
    ic->waitForShutdown();
}
