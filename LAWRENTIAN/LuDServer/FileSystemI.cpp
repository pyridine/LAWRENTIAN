#include "FileSystemI.h"
#include <fstream>
#include <direct.h>
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include <vector>
#include <stack>
#include <stdio.h>
#include <algorithm>

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

    consolePrint("===" + caller_info + "===" );

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

    consolePrint("receiveLatest: " + dir);

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

    consolePrint("===" + caller_info + "===" );

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
    consolePrint("receiveVersion: " + dir);

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
    consolePrint("===" + caller_info + "===" );

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
    consolePrint("sendFile: " + dir);

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
    consolePrint("===" + caller_info + "===" );

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
    consolePrint("getHistory: " + fName + " has "
                 + std::to_string((long long)v_seq.size() - 1) + " version(s).");
    return v_seq;
}

/*FileSystem::*/
std::vector<std::string> FileSystemI::getImageList(const std::string &sec, const std::string &art/*,
                                             const Ice::Current &c*/)
{
    using namespace std;
    using namespace FileSystem;

    std::vector<std::string> seq;
    vector<string> list;
    string dir = main_dir + "/" + sec + "/" + art + "/" + IMAGE;
    if(!listFiles(dir,"*",list))
        return seq;
    cout << 12 << endl;
    vector<string>::const_iterator iter = list.begin();
    cout << 2 << endl;
    string prev_folder = "";
    cout << 3 << endl;
    while(iter != list.end())
    {
        string folder = extractFolderName(*iter);
        cout << 4 << endl;
        if(!prev_folder.compare(folder))
            seq.push_back(folder);
        cout << 5 << endl;
        prev_folder = folder;
        iter++;

    }
    return seq;
}

bool FileSystemI::changeDir(const std::string &sec, const std::string &art_old,
                            const std::string &art_new, const Ice::Current& c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string f_old = main_dir + "/" + sec + "/" + art_old;
    string f_new = main_dir + "/" + sec + "/" + art_new;

    if(dirExists(f_old))
        rename( f_old.c_str() , f_new.c_str() );
    else
    {
        consolePrint("changeDir: " + art_old + " does not exist!");
        return false;
    }

    f_old = f_new + "/" + COPY + "/" + art_old;
    f_new = f_new + "/" + COPY + "/" + art_new;

    if(dirExists(f_old))
        rename( f_old.c_str(), f_new.c_str());
    else
    {
        consolePrint("changeDir: no files to change!");
        return false;
    }

    string fNameExt_old = f_new + "/" + art_old + ".docx";
    string fNameExt_new = f_new + "/" + art_old + ".docx";

    long long i = 0;
    while(true)
    {
        string file_old = i ? insertCorrectly(fNameExt_old, std::to_string(i).c_str())
                            : fNameExt_old;
        string file_new = i ? insertCorrectly(fNameExt_new, std::to_string(i).c_str())
                            : fNameExt_new;

        ifstream check(file_old, ios::binary);
        if(check)
            rename(file_old.c_str(), file_new.c_str());
        else
            break;
        i++;
    }

    consolePrint("changeDir: successfully changed name to " + art_new);
    return true;
}

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

std::string FileSystemI::insertCorrectly(const std::string& str, const char* num)
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
    string ret = str;
    ret.insert(iter - str.begin(), num);

    return ret;
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

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    strftime(buf, sizeof(buf), "%m-%d-%Y %X", &tstruct);

    if(str[1] == '=')
    {
        string temp(buf);
        string t = "[" + temp + "]: ";
        cout << t << str;

        if(str.size() != 80 - t.size())
            cout << endl;
    }
    else
    {
        std::cout << str;

        if(str.size() != 80)
            cout << endl;
    }
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

bool FileSystemI::deleteDirectory(const std::string &dir)
{
    using namespace std;

    vector<wstring> files;
    vector<string> folders;

    string path = dir;
    wstring wPath(path.begin(), path.end());

    if (listFiles(wPath, L"*", files))
    {
        vector<wstring>::const_iterator it = files.begin();

        for (it; it != files.end(); it++)
        {
            if(!remove(fixPath(it->c_str()).c_str()));
                return false;
        }

        getFolders(files,folders,path);
        vector<string>::iterator iter = folders.begin();
        for (iter; iter != folders.end(); iter++)
        {
            string str = fixPath(*iter);
            wstring temp(str.begin(),str.end());
            const wchar_t *fn = temp.c_str();
            LPCTSTR folder_name = fn;
            if(!RemoveDirectory( folder_name ))
                return false;
        }

    }
    return true;
}


bool FileSystemI::deleteArt(const std::string &sec, const std::string &art,
                            const Ice::Current& c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string path = main_dir + "/" + sec + "/" + art;

    if(deleteDirectory(path))
    {
        consolePrint("deleteArt: " + path);
        return true;
    }
    return false;
}

bool FileSystemI::deleteAllImages(const std::string &sec, const std::string &art, const Ice::Current &c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string path = main_dir + "/" + sec + "/" + art + "/" + IMAGE;

    if(deleteDirectory(path))
    {
        consolePrint("deleteAllImages: " + path);
        return true;
    }
    return false;
}

bool FileSystemI::deleteImage(const std::string &sec, const std::string &art, const std::string &name, const Ice::Current &c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string path = main_dir + "/" + sec + "/" + art + "/" + IMAGE + "/" + name;

    if(deleteDirectory(path))
    {
        consolePrint("deleteImage: " + path);
        return true;
    }
    return false;
}

bool FileSystemI::deleteAllCopies(const std::string &sec, const std::string &art, const Ice::Current &c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string path = main_dir + "/" + sec + "/" + art + "/" + COPY;

    if(deleteDirectory(path))
    {
        consolePrint("deleteAllCopies: " + path);
        return true;
    }
    return false;

}

bool FileSystemI::deleteCopyVer(const std::string &sec, const std::string &art, const int ver, const Ice::Current &c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string path = main_dir + "/" + sec + "/" + art + "/" + COPY + "/" + art + ".docx";
    path = ver ? insertCorrectly(path,std::to_string((long long)ver).c_str()) : path;

    if(!remove(path.c_str()))
    {
        consolePrint("deleteCopyVer: " + path);
        return true;
    }
    return false;
}

std::string FileSystemI::fixPath(const std::wstring& p)
{
    using namespace std;

    string path( p.begin(), p.end() );
    string::iterator iter = path.begin();
    for(iter; iter != path.end(); iter++)
    {
        if(*iter == '\\')
            *iter = '/';
    }
    return path;
}

std::string FileSystemI::fixPath(const std::string& p)
{
    using namespace std;

    string path = p;
    string::iterator iter = path.begin();
    for(iter; iter != path.end(); iter++)
    {
        if(*iter == '\\')
            *iter = '/';
    }
    return path;
}

bool FileSystemI::listFiles(std::string path, std::string mask, std::vector<std::string>& files)
{
    using namespace std;

    vector<wstring> out;
    wstring p(path.begin(), path.end());
    wstring m(mask.begin(), mask.end());

    if(!listFiles(p,m,out))
        return false;

    vector<wstring>::const_iterator iter;
    while(iter != out.end())
    {
        wstring ws = *iter;
        string s(ws.begin(), ws.end());
        files.push_back(s);
        iter++;
    }
    return true;

}

std::string FileSystemI::extractFolderName(const std::string &s)
{
    using namespace std;

    string::const_iterator it, iter = s.end() - 1;
    while(*iter != '/')
    {
        if(iter == s.begin())
            return "";
        iter--;
    }
    iter--;
    it = iter;
    while(*it != '/')
    {
        if(it == s.begin())
            return "";
        it--;
    }
    it++;
    return s.substr(it-s.begin(),iter-it +1);}


bool FileSystemI::listFiles(std::wstring path, std::wstring mask, std::vector<std::wstring>& files)
{
    using namespace std;

    HANDLE hFind = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA ffd;
    wstring spec;
    stack<wstring> directories;

    directories.push(path);
    files.clear();

    while (!directories.empty()) {
        path = directories.top();
        spec = path + L"\\" + mask;
        directories.pop();

        hFind = FindFirstFile(spec.c_str(), &ffd);
        if (hFind == INVALID_HANDLE_VALUE)  {
            return false;
        }

        do {
            if (wcscmp(ffd.cFileName, L".") != 0 &&
                    wcscmp(ffd.cFileName, L"..") != 0) {
                if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    directories.push(path + L"\\" + ffd.cFileName);
                }
                else {
                    files.push_back(path + L"\\" + ffd.cFileName);
                }
            }
        } while (FindNextFile(hFind, &ffd) != 0);

        if (GetLastError() != ERROR_NO_MORE_FILES) {
            FindClose(hFind);
            return false;
        }

        FindClose(hFind);
        hFind = INVALID_HANDLE_VALUE;
    }

    return true;
}

void FileSystemI::getFolders(const std::vector<std::wstring> vec, std::vector<std::string>& out,
           const std::string& m_p)
{
    using namespace std;

    string main_path = fixPath(m_p);
    vector<wstring>::const_iterator iter = vec.begin();
    while(iter != vec.end())
    {
        wstring temp = *iter;

        string dir(temp.begin(), temp.end());

        while(main_path.compare(dir))
        {
            if(!dir.size())
                return;

            dir = fixPath(dir);

            string::const_iterator it = dir.end() - 1;
            for(it; it != dir.begin(); it--)
            {
                if (*it == '/')
                    break;
            }
            if(it == dir.begin())
                return;

            dir.resize(it - dir.begin());
            vector<string>::const_iterator i = std::find(out.begin(),out.end(),dir);
            if(main_path.compare(dir) && i == out.end())
                out.push_back(dir);
        }

        iter++;
    }

    sort(out.begin(), out.end(), greater<string>());
    out.push_back(fixPath(main_path));
    return;
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
