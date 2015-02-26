#include "FileSystemI.h"
#include <fstream>
#include <Windows.h>
#include <string.h>
#include <direct.h>
#include <cctype>

FileSystemI::FileSystemI()
{
    using namespace std;

    COPY = "Copy";
    IMAGE = "Image";

    main_dir = "C:/Users/Briggs 419 Server/Dropbox/Issue";
}

FileSystemI::FileSystemI(std::string main_node)
{
    using namespace std;

    COPY = "Copy";
    IMAGE = "Image";

    main_dir = main_node;
}

FileSystem::ByteSeq
FileSystemI::receiveLatest(const std::string& sec, const std::string& art,
                           const std::string& type, const std::string& fName_p,
                           const Ice::Current& c)
{
    using namespace std;
    using namespace FileSystem;

    ByteSeq seq;

    string caller_info = getName(getIP(c));

    cout << "===" + caller_info + "===" << endl;

    string fName = getfName(fName_p);
    string path = main_dir + "/" + sec + "/" + art + "/" + type
            + "/" + fName;

    string fn;

    if(!type.compare(COPY))
        fn = fName + ".docx";
    else if(!type.compare(IMAGE))
        fn = fName + ".jpg";
    else
        return seq;
    long long i = 1;
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
            else if(i != 1)
                break;
            else
                return seq;
            check.close();
        }
    }
    else
    {
        cout << path << endl << "Path does not exist" << endl; // throw exception in the future.
        return seq;
    }

    consolePrint("request path: " + path);
    consolePrint("request: " + dir);
    ifstream source(dir,ios::binary);

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

FileSystem::ByteSeq
FileSystemI::receiveVersion(const std::string& sec, const std::string& art,
                           const std::string& type, const std::string& fName_p,
                           const int ver, const Ice::Current& c)
{
    using namespace std;
    using namespace FileSystem;

    ByteSeq seq;
    string fName = getfName(fName_p);

    if (ver == -1)
        return receiveLatest(sec, art, type, fName, c);   

    string caller_info = getName(getIP(c));

    cout << "===" + caller_info + "===" << endl;

    string path = main_dir + "/" + sec + "/" + art + "/" + type
            + "/" + fName;

    string dir;
    if (dirExists(path))
    {
        long long ver_num = ver;

        string fn;
        if(!type.compare(COPY))
            fn = (ver) ? fName + std::to_string(ver_num) + ".docx"
                       : fName + ".docx";
        else if(!type.compare(IMAGE))
            fn = (ver) ? fName + std::to_string(ver_num) + ".jpg"
                       : fName + ".jpg";
        else
            return seq;

        dir = path + "/" + fn;
        ifstream check(dir, ios::binary);
        if (!check)
            return seq;
        check.close();
    }
    else
    {
        cout << path << endl << "Path does not exist" << endl; // throw exception in the future.
        return seq;
    }
    consolePrint("request path: " + path);
    consolePrint("request: " + dir);
    ifstream source(dir,ios::binary);

    source.seekg(0, ios::end);
    long len = source.tellg();
    source.seekg(0, ios::beg);

    seq.resize(len);
    source.read(reinterpret_cast<char*>(&seq[0]), seq.size());

    return seq;
}

bool
FileSystemI::sendFile(const std::string& sec, const std::string& art,
                      const std::string& type, const std::string& fNameExt,
                      const FileSystem::ByteSeq& seq, const Ice::Current& c)
{
    using namespace std;
    using namespace FileSystem;

    string caller_info = getName(getIP(c));
    cout << "===" + caller_info + "===" << endl;

    string sec_dir = sec;
    string article_dir = art;
    string type_dir = type;
    string file_dir = extractFileName(fNameExt);

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

    string temp = dir + "/" + fNameExt;
    string fn = fNameExt;
    ifstream file(fixExtension(temp,type),ios::binary);
    while(true){
        if (!file)
            break;
        else
        {
            insertCorrectly(fn,std::to_string(num).c_str());
            temp = dir + "/" + fn;
            file = ifstream(fixExtension(temp,type), ios::binary);
            if(file)
                fn = fNameExt;
        }
        num++;
    }
    dir = dir + "/" + fn;
    file.close();
    consolePrint("send name: " + fNameExt);
    consolePrint("send: " + dir);

    ofstream dest(fixExtension(dir,type), ios::binary);
    dest.write(reinterpret_cast<const char*>(&seq[0]),seq.size());

    bool status = dest ? true : false;
    dest.close();

    return status;
}

FileSystem::VerSeq
FileSystemI::getHistory(const std::string& sec, const std::string& art,
         const std::string& type, const std::string& fName,
         const Ice::Current& c)
{
    using namespace std;
    using namespace FileSystem;

    VerSeq v_seq;

    string caller_info = getName(getIP(c));
    cout << "===" + caller_info + "===" << endl;

    string path = main_dir + "/" + sec + "/" + art + "/" + type
            + "/" + fName;

    string fn;
    if (!type.compare(COPY))
        fn = fName + ".docx";
    else if (!type.compare(IMAGE))
        fn = fName + ".jpg";
    else
        return v_seq;

    long long i = 0;
    if (dirExists(path))
    {
        string temp_fn = fn;
        while(true)
        {
            string dir = path + "/" + fn;

            ifstream check(dir, ios::binary);

            if(check)
            {
                Version vr;
                vr.verNum = (int)i;
                vr.verName = i ? fName + "*" + std::to_string(i) : fName;
                getCreationTime(dir,vr.time);

                v_seq.push_back(vr);
                i++;
            }
            else if (i)
                break;
            else
            {
                Version vr;
                vr.verNum = 0;
                vr.verName = "No Version";
                TimeIce t;
                vr.time = t;
                v_seq.push_back(vr);

                return v_seq;
            }
            fn = temp_fn;
            insertCorrectly(fn, std::to_string(i).c_str());
            check.close();
        }
    }
    else
    {
        cout << path << endl << "Path does not exist" << endl; // throw exception in the future.
        return v_seq;
    }
    consolePrint("number of versions of " + fName + ": "
                 + std::to_string((long long)v_seq.size() - 1));
    return v_seq;
}

// got from StackExchange
bool FileSystemI::getCreationTime(const std::string &path, FileSystem::TimeIce& t)
{
    using namespace std;

    FILETIME ftCreate, ftAccess, ftWrite;
    SYSTEMTIME stUTC, stLocal;
    HANDLE hFile;

    wstring stemp = wstring(path.begin(), path.end());
    LPCWSTR name = stemp.c_str();

    hFile = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, NULL,
                       OPEN_EXISTING, 0, NULL);

    if(hFile == INVALID_HANDLE_VALUE)
    {
        printf("CreateFile failed with %d\n", GetLastError());
        return false;
    }

    // Retrieve the file times for the file.
    if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
        return false;

    // Convert the last-write time to local time.
    FileTimeToSystemTime(&ftCreate, &stUTC);
    SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

    int num = stLocal.wDayOfWeek;
    switch(num)
    {
    case 1:
        t.dayOfTheWeek = "Monday";
        break;
    case 2:
        t.dayOfTheWeek = "Tuesday";
        break;
    case 3:
        t.dayOfTheWeek = "Wednesday";
        break;
    case 4:
        t.dayOfTheWeek = "Thursday";
        break;
    case 5:
        t.dayOfTheWeek = "Friday";
        break;
    case 6:
        t.dayOfTheWeek = "Saturday";
        break;
    case 7:
        t.dayOfTheWeek = "Sunday";
        break;
    }

    t.day = (int)stLocal.wDay;
    t.month = (int)stLocal.wMonth;
    t.year = (int)stLocal.wYear;
    t.hour = (int)stLocal.wHour;
    t.minute = (int)stLocal.wMinute;
    t.second = (int)stLocal.wSecond;
    t.milliseconds = (int)stLocal.wMilliseconds;

    return true;

}

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
    names.insert(pair_str("143.44.10.35","Briggs 419 Server"));

    map_str::const_iterator iter = names.find(ip_address);
    return iter == names.end() ? "UNIDENTIFIED: " + ip_address : iter->second;
}

std::string FileSystemI::getfName(const std::string& s)
{
    using namespace std;

    string str = s;

    string::const_iterator iter = str.begin();
    for (iter; iter != str.end(); iter++)
    {
        if(*iter == '*')
            break;
    }

    str.resize(iter - str.begin());
    return str;
}

std::string FileSystemI::fixExtension(const std::string &s, const std::string &type)
{
    using namespace std;

    string ext;
    if(!type.compare(COPY))
        ext = ".docx";
    else if(!type.compare(IMAGE))
        ext = ".jpg";
    else
        return NULL;

    string::const_iterator iter = s.end() - 1;
    for(iter; iter!=s.begin(); iter--)
    {
        if(*iter == '.')
            break;
    }

    return s.substr(0,iter - s.begin()) + ext;

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
