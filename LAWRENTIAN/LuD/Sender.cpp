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
Sender::sendFile(const std::string& issueDate, const std::string& sec,
                 const std::string& art, const std::string& type, const std::string& clDir)
{
    using namespace std;
    using namespace Ice;

    ifstream source(clDir, ios::binary);
    source.seekg(0, ios::end);
    long len = source.tellg();
    source.seekg(0, ios::beg);

    ByteSeq seq(len);
    source.read(reinterpret_cast<char*>(&seq[0]), seq.size());

    bool b = fpx->sendFile(issueDate, sec, art, type, art,seq);
    source.close();

    return b;
}

bool
Sender::requestFile(const std::string& issueDate, const std::string& sec,
                    const std::string& art, const std::string& type, const std::string& down_dir,
                    int ver)
{
    using namespace std;
    using namespace Ice;

    ByteSeq seq = (ver == -1)
                ? fpx->receiveLatest(issueDate, sec, art, type, art)
                : fpx->receiveVersion(issueDate, sec, art, type, art, ver);

    if (!seq.size())
        return false;

    ofstream dest(down_dir, ios::binary);

    dest.write(reinterpret_cast<char*>(&seq[0]),seq.size());
    return dest ? true : false;
}

FileSystem::VerSeq
Sender::getHistory(const std::string& issueDate, const std::string& sec, const std::string& art,
                   const std::string& type)
{
    return fpx->getHistory(issueDate, sec, art, type, art);
}

FileSystem::StrSeq Sender::getImageList(const std::string &issueDate, const std::string &sec, const std::string &art)
{
    return fpx->getImageList(issueDate, sec, art);
}

bool Sender::renameArticle(const std::string &issueDate, const std::string &sec, const std::string &artOld, const std::string &artNew)
{
    return fpx->changeDir(issueDate,sec,artOld,artNew);
}

bool Sender::moveArtToSection(const std::string &issueDate, const std::string &secOld, const std::string &secNew, const std::string &art)
{
    return fpx->moveArtToSection(issueDate, secOld, secNew, art);
}

bool Sender::archiveIssue(const std::string &issueDate)
{
    return fpx->archiveIssue(issueDate);
}

bool Sender::deleteArt(const std::string &issueDate, const std::string &sec, const std::string &art)
{
    return fpx->deleteArt(issueDate, sec, art);
}

bool Sender::deleteAllImages(const std::string &issueDate, const std::string &sec, const std::string &art)
{
    return fpx->deleteAllImages(issueDate, sec, art);
}

bool Sender::deleteImage(const std::string &issueDate, const std::string &sec, const std::string &art, const std::string &name)
{
    return fpx->deleteImage(issueDate,sec,art,name);
}

bool Sender::deleteAllCopies(const std::string &issueDate, const std::string &sec, const std::string &art)
{
    return fpx->deleteAllCopies(issueDate, sec, art);
}

bool Sender::deleteCopyVer(const std::string &issueDate, const std::string &sec, const std::string art, int ver)
{
    return fpx->deleteCopyVer(issueDate, sec, art, ver);
}











