#include "FileSystemI.h"
#include <fstream>
#include <Windows.h>
#include <string.h>
#include <direct.h>
#include <cctype>

FileSystemI::FileSystemI()
{
    using namespace std;
    main_dir = "C:/Users/Briggs 419 Server/Dropbox";
}

FileSystemI::FileSystemI(std::string main_node)
{
    using namespace std;
    main_dir = main_node;
}

Ice::ByteSeq FileSystemI::receiveFile(const std::string& path,
                                      const Ice::Current& c)
{
    using namespace std;
    using namespace Ice;

    string caller_info = getName(getIP(c));

    cout << "===" + caller_info + "===" << endl;

    // create file name.
    string fn = extractNodeName(path) + ".docx";

    // returns latest version only.
    long long i = 1;

    // because path is type const string (requied by Ice)
    string dir;
    if (dirExists(path))
    {
        string temp_dir = path + "/" + fn;
        while(true)
        {
            dir = temp_dir;
            temp_dir = path + "/" + fn;
            insertCorrectly(temp_dir, std::to_string(i).c_str());

            ifstream check(temp_dir, ios::binary);
            if(check)
                i++;
            else
                break;
            check.close();

        }
    }
    else
        cout << path << endl << "Path does not exist" << endl; // throw exception in the future.
    consolePrint("request path: " + path);
    consolePrint("request: " + dir);
    ifstream source(dir,ios::binary);

    ByteSeq seq;
    seq.push_back('c');
    if(dir.size() != 0)
    {
        source.seekg(0, ios::end);
        long len = source.tellg();
        source.seekg(0, ios::beg);

        seq.resize(len);
        source.read(reinterpret_cast<char*>(&seq[0]), seq.size());
    }
    else
        cout << dir << " does not exist" << endl; // throw exception in future.
    return seq;
}

bool FileSystemI::sendFile(const std::string& name_sf, const Ice::ByteSeq& seq,
                           const Ice::Current& c)
{
    using namespace std;
    using namespace Ice;

    string caller_info = getName(getIP(c));
    cout << "===" + caller_info + "===" << endl;

    string sec_dir = "Article";
    string article_dir = "Document";
    string type_dir = "Copy";
    string file_dir = extractFileName(name_sf);

    string dir = main_dir + "/" + sec_dir + "/" + article_dir
            + "/" + type_dir + "/" + file_dir;
    if(!dirExists(dir))
    {
        string temp = main_dir;
        mkdir( (temp + "/" + sec_dir).c_str());

        temp = temp + "/" + sec_dir;
        mkdir( (temp + "/" + article_dir).c_str());

        temp = temp + "/" + article_dir;
        mkdir( (temp + "/" + type_dir).c_str());

        temp = temp + "/" + type_dir;
        mkdir( (temp + "/" + file_dir).c_str());

    }


    long long num = 1; // bug MSV2010.

    string temp = dir + "/" + name_sf;
    string fn = name_sf;
    ifstream file(temp,ios::binary);
    while(true){
        if (!file)
            break;
        else
        {
            insertCorrectly(fn,std::to_string(num).c_str());
            temp = dir + "/" + fn;
            file = ifstream(temp, ios::binary);
            if(file)
                fn = name_sf;
        }
        num++;
    }
    dir = dir + "/" + fn;
    file.close();
    consolePrint("send name: " + name_sf);
    consolePrint("send: " + dir);

    ofstream dest(dir, ios::binary);
    dest.write(reinterpret_cast<const char*>(&seq[0]),seq.size());

    bool status = dest ? true : false;
    dest.close();

    return status;
}

// got from StackExchange
bool FileSystemI::dirExists(const std::string& dir)
{
    DWORD ftyp = GetFileAttributesA(dir.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory!

    return false;    // this is not a directory!
}

std::string FileSystemI::extractFileName(const std::string& str)
{
    using namespace std;

    string name = str;
    string::const_iterator iter = name.end() - 1;
    while(*iter != '.')
    {
        iter--;
        if(iter == name.begin())
        {
            break; // throw exception.
            cout << "broken" << endl;
        }
    }
    name.resize(iter - name.begin());

    return name;
}

std::string FileSystemI::insertCorrectly(std::string& str, const char* num)
{
    using namespace std;

    string::const_iterator iter = str.end() - 1;
    while(*iter != '.')
    {
        iter--;
        if(iter == str.begin())
        {
            break; // throw exception.
            cout << "broken" << endl;
        }
    }
    str.insert(iter - str.begin(), num);

    return str;
}

std::string FileSystemI::extractNodeName(const std::string str)
{
    using namespace std;

    string::const_iterator iter = str.end() - 1;
    while(*iter != '/' && *iter != '\\')
    {
        iter--;
        if(iter == str.begin())
        {
            break; //throw exception.
            cout << "broken" << endl;
        }
    }
    return str.substr(iter - str.begin() + 1,str.end() - iter - 1);
}

// copied from Ice manual.
std::string FileSystemI::getIP(const Ice::Current& c)
{
    using namespace std;
    using namespace Ice;

    ConnectionInfoPtr info = c.con->getInfo();
    TCPConnectionInfoPtr tcpInfo = Ice::TCPConnectionInfoPtr::dynamicCast(info);
    return tcpInfo ? tcpInfo->remoteAddress : "UNIDENTIFIED";
}

void FileSystemI::consolePrint(const std::string& str)
{
    using namespace std;

    cout << str;
    if(str.size() != 80)
        cout << endl;
}

std::string FileSystemI::getName(const std::string& ip_address)
{
    using namespace std;

    typedef map<const string,const string> map_str;
    typedef pair<const string,const string> pair_str;

    map_str names;

    names.insert(pair_str("143.44.76.61","Sanfer D'souza"));
    names.insert(pair_str("143.44.65.151","Jordan Mark"));
    names.insert(pair_str("143.44.68.218","Lisa Girsova"));

    map_str::const_iterator iter = names.find(ip_address);
    return iter == names.end() ? "UNIDENTIFIED: " + ip_address : iter->second;
}

/* FOR SOME REASON ICE DOES NOT ALLOW ME TO USE find().
std::string FileSystemI::extractFileName(const std::string& str)
{
   using namespace std;

   string name = str;
   int pos = name.rfind('.');
   name.resize(pos);

   return name;
}
*/
