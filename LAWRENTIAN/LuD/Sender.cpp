#include "Sender.h"
#include <vector>

Sender::Sender()
{
    ic = Ice::initialize();
    Ice::ObjectPrx base = ic->stringToProxy(
                "FileSystem:default-p 10000");
    fpx = FileSystem::FilePrx::checkedCast(base);
    if (!fpx)
        throw "Invalid proxy";
}

Sender::~Sender()
{
    if(ic)
        ic->destroy();
}

// dir_sf -> directory of file to send.
void Sender::sendFile(std::string dir_sf,
                      std::vector<std::string> art_info)
{
    using namespace std;
    using namespace FileSystem;

    ifstream source(dir_sf,ios::binary);
    source.seekg(0, ios::end);
    long len = source.tellg();
    source.seekg(0, ios::beg);

    Ice::ByteSeq seq(len);
    source.read(reinterpret_cast<char*>(&seq[0]), seq.size());
    FileInfo info;
    info.bs = seq, info.ss = art_info;

    fpx->sendFile(info);
    source.close();
}

std::ofstream Sender::requestFile(std::string file_name,
                                  std::vector<std::string>* str_vec)
{
    using namespace std;
    using namespace FileSystem;

    FileInfo info = fpx->receiveFile(file_name);
    Ice::ByteSeq seq = info.bs;

    ofstream dest;
    dest.write(reinterpret_cast<char*>(&seq[0]),seq.size());

    *str_vec = info.ss;
    dest.close();
    return dest;
}
