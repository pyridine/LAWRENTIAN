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

bool
Sender::sendFile(const std::string& sec, const std::string& art,
                 const std::string& type, const std::string& fNameExt,
                 const std::string& clDir)
{
    using namespace std;
    using namespace Ice;

    ifstream source(clDir, ios::binary);
    source.seekg(0, ios::end);
    long len = source.tellg();
    source.seekg(0, ios::beg);

    ByteSeq seq(len);
    source.read(reinterpret_cast<char*>(&seq[0]), seq.size());

    bool b = fpx->sendFile(sec, art, type, fNameExt,seq);
    source.close();

    return b;
}

bool
Sender::requestFile(const std::string& sec, const std::string& art,
                    const std::string& type, const std::string& fName,
                    const std::string& down_dir, int ver)
{
    using namespace std;
    using namespace Ice;

    ByteSeq seq = (ver == -1)
                ? fpx->receiveLatest(sec, art, type, fName)
                : fpx->receiveVersion(sec, art, type, fName, ver);

    if (!seq.size())
        return false;

    ofstream dest(down_dir, ios::binary);

    dest.write(reinterpret_cast<char*>(&seq[0]),seq.size());
    return dest ? true : false;
}

FileSystem::VerSeq
Sender::getHistory(const std::string& sec, const std::string& art,
                   const std::string& type, const std::string& fName)
{
    return fpx->getHistory(sec, art, type, fName);
}

