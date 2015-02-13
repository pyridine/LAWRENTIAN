#include <Ice/Ice.h>
#include "Sender.h"
#include "FileSystem.h"
#include <fstream>
#include <vector>

static const std::string connection = "tcp -h 143.44.10.35 -p 10001";
Sender::Sender()
{
    using namespace std;

    ic = Ice::initialize();
    Ice::ObjectPrx base = ic->stringToProxy("FileSystem:" + connection);
    fpx = FileSystem::FilePrx::checkedCast(base);
}

Sender::Sender(const std::string& con)
{
    using namespace std;

    ic = Ice::initialize();
    Ice::ObjectPrx base = ic->stringToProxy("FileSystem:" + connection);
    fpx = FileSystem::FilePrx::checkedCast(base);
}

Sender::Sender(const int& num)
{
    using namespace std;

    ic = Ice::initialize();
    Ice::ObjectPrx base = num ? ic->stringToProxy("FileSystem:" + connection) : ic->stringToProxy("FileSystem:default -p 10000");
    fpx = FileSystem::FilePrx::checkedCast(base);
}

Sender::~Sender()
{
    if(ic)
        ic->destroy();
}

// dir_sf -> directory of file to send.
bool Sender::sendFile(const std::string& dir_sf, const std::string& name)
{
    using namespace std;
    using namespace Ice;

    cout << dir_sf << endl << name << endl;

    ifstream source(dir_sf, ios::binary);
    source.seekg(0, ios::end);
    long len = source.tellg();
    source.seekg(0, ios::beg);

    ByteSeq seq(len);
    source.read(reinterpret_cast<char*>(&seq[0]), seq.size());

    bool b = fpx->sendFile(name,seq);
    source.close();

    return b;
}

// dir_rf: directory of receive file    down_dir: directory of downloaded file
bool Sender::requestFile(const std::string& dir_rf, const std::string& down_dir)
{
    using namespace std;
    using namespace Ice;

    ByteSeq seq = fpx->receiveFile(dir_rf);
    ofstream dest(down_dir, ios::binary);

    dest.write(reinterpret_cast<char*>(&seq[0]),seq.size());

    bool b = dest ? true : false;
    return b;
}
