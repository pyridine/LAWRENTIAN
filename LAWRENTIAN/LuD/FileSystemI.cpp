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

    main_dir = "C:/Users/Briggs 419 Server/Dropbox/Issue";
    arc_dir = "C:/Users/Briggs 419 Server/Dropbox/Archive";
}

FileSystemI::FileSystemI(std::string main_node)
{
    using namespace std;

    main_dir = main_node;
    arc_dir = "C:/Users/Briggs 419 Server/Dropbox/Archive";
}

FileSystem::ByteSeq
FileSystemI::receiveLatest(const std::string& issue_date, const std::string& sec,
                           const std::string& art, const std::string& type,
                           const std::string& fName, const Ice::Current& c)
{
    using namespace std;
    using namespace FileSystem;

    ByteSeq seq;

    string caller_info = getName(getIP(c));

    consolePrint("===" + caller_info + "===" );

    string path =  main_dir + "/" + issue_date + "/" + sec + "/" + art + "/" + type
            + "/" + fName;

    string fNameExt;
    if(!type.compare(fs::COPY))
        fNameExt = fName + fs::extCOPY;
    else if(!type.compare(fs::IMAGE))
        fNameExt = fName + fs::extIMAGE;
    else
        return seq;

    int ver_num = 1;
    string dir;
    if (dirExists(path))
    {
        string temp_dir = path + "/" + fNameExt;
        ifstream check;
        check.open(temp_dir, ios::binary);

        if(!check.is_open())
        {
            /* FileSystem is set such that the first file is only the article name without version number.
             * In such a restriction, the algorithm below works.
             */

            string folder_path = extractNodeName(temp_dir);
            if(removeFolder(folder_path))
                consolePrint("receiveLatest: " + folder_path + " is empty! Deleted.");
            else
                consolePrint("receiveLatest: " + folder_path + " is emply! Manual deletion required.");
            return seq;
        }

        while(check.is_open())
        {
            dir = temp_dir;
            temp_dir = path + "/" + fNameExt;
            insertCorrectly(temp_dir, ver_num);

            check.close();
            check.open(temp_dir, ios::binary);
            ver_num++;
        }
    }
    else
    {
        consolePrint("receiveLatest: " + path + " does not exist."); // throw exception in the future.
        return seq;
    }

    ifstream source;
    source.open(dir,ios::binary);

    if(dir.size())
    {
        source.seekg(0, ios::end);
        streamoff len = source.tellg();
        source.seekg(0, ios::beg);

        seq.resize(len);
        source.read(reinterpret_cast<char*>(&seq[0]), seq.size());
    }
    else
    {
        consolePrint(dir + " not found. :("); // throw exception in future.
        return seq;
    }

    consolePrint("receiveLatest: " + dir + " is found!");
    return seq;
}

FileSystem::ByteSeq
FileSystemI::receiveVersion(const std::string& issue_date, const std::string& sec,
                            const std::string& art, const std::string& type, const std::string& fName,
                            const int ver, const Ice::Current& c)
{
    using namespace std;
    using namespace FileSystem;

    if (ver == -1) return receiveLatest(issue_date, sec, art, type, fName, c);

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    ByteSeq seq;
    // string fName = fName_p;

    string path =  main_dir + "/" + issue_date + "/" + sec + "/" + art + "/" + type
            + "/" + fName;

    string dir;
    if (dirExists(path))
    {
        long long ver_num = ver;

        string fNameExt;
        if(!type.compare(fs::COPY))
            fNameExt = (ver) ? fName + std::to_string(ver_num) + fs::extCOPY
                             : fName + fs::extCOPY;
        else if(!type.compare(fs::IMAGE))
            fNameExt = (ver) ? fName + std::to_string(ver_num) + fs::extIMAGE
                             : fName + fs::extIMAGE;
        else
        {
            consolePrint("receiveVersion: " + type + " is invalid type.");
            return seq;
        }

        dir = path + "/" + fNameExt;
        ifstream check;
        check.open(dir, ios::binary);
        if (!check.is_open())
        {
            consolePrint("receiveVersion: invalid version number.");
            return seq;
        }
    }
    else
    {
        consolePrint("receiveVersion: " + path + " does not exist."); // throw exception in the future.
        return seq;
    }

    ifstream source;
    source.open(dir,ios::binary);

    source.seekg(0, ios::end);
    streamoff len = source.tellg();
    source.seekg(0, ios::beg);

    seq.resize(len);
    source.read(reinterpret_cast<char*>(&seq[0]), seq.size());

    consolePrint("receiveVersion: " + dir + " found.");
    return seq;
}

bool
FileSystemI::sendFile(const std::string& issue_date, const std::string& sec,
                      const std::string& art, const std::string& type,
                      const std::string& fName, const FileSystem::ByteSeq& seq,
                      const Ice::Current& c)
{
    using namespace std;
    using namespace FileSystem;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string dir =  main_dir + "/" + issue_date + "/" + sec + "/" + art
            + "/" + type + "/" + fName;
    if(!dirExists(dir))
    {
        string temp = main_dir;
        _mkdir( (temp + "/" + sec).c_str());

        temp = temp + "/" + sec;
        _mkdir( (temp + "/" + art).c_str());

        temp = temp + "/" + art;
        _mkdir( (temp + "/" + type).c_str());

        temp = temp + "/" + type;
        _mkdir( (temp + "/" + fName).c_str());

        consolePrint("sendFile: " + dir + " created.");
    }

    int ver = 1; // bug MSV2010.

    string fNameExt = addExtension(fName, type);
    string fNameExt_clean = fNameExt;
    ifstream file;
    file.open(dir + "/" + fNameExt,ios::binary);

    while(file.is_open())
    {
        fNameExt = fNameExt_clean;
        insertCorrectly(fNameExt,ver);
        string temp_dir = dir + "/" + fNameExt;
        file.close();
        file.open(temp_dir, ios::binary);
        ver++;
    }
    file.close();
    dir = dir + "/" + fNameExt;

    ofstream dest;
    dest.open(fixExtension(dir,type), ios::binary);
    dest.write(reinterpret_cast<const char*>(&seq[0]),seq.size());

    bool status = dest ? true : false;

    if(status)
        consolePrint("sendFile: " + dir + " successfully saved!");
    else
        consolePrint("sendFile: " + dir + " addition unsuccessful.");

    return status;
}

FileSystem::VerSeq
FileSystemI::getHistory(const std::string& issue_date, const std::string& sec,
                        const std::string& art, const std::string& type,
                        const std::string& fName, const Ice::Current& c)
{
    using namespace std;
    using namespace FileSystem;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    VerSeq v_seq;

    string path =  main_dir + "/" + issue_date + "/" + sec + "/" + art + "/" + type
            + "/" + fName;

    string fNameExt = addExtension(fName, type);
    if(!fNameExt.compare(NULL))
    {
        consolePrint("getHistory: " + type + " invalid.");
        return v_seq;
    }

    int ver_num = 0;
    if (dirExists(path))
    {
        string fNameExt_clean = fNameExt;

        string dir = path + "/" + fNameExt;

        ifstream check;
        check.open(dir,ios::binary);

        if(!check.is_open())
        {
            /* FileSystem is set such that the first file is only the article name without version number.
             * In such a restriction, the algorithm below works.
             */

            string folder_path = extractNodeName(dir);
            if(removeFolder(folder_path))
                consolePrint("getHistory: " + folder_path + " is empty! Deleted.");
            else
                consolePrint("getHistory: " + folder_path + " is emply! Manual deletion required.");
            return v_seq;
        }

        while(check.is_open())
        {
            Version vr;
            vr.verNum = (int)ver_num;
            vr.verName = ver_num ? fName + std::to_string((long long)ver_num) : fName;
            getCreationTime(dir,vr.time);

            v_seq.push_back(vr);
            ver_num++;

            fNameExt = insertCorrectly(fNameExt_clean, ver_num);
            dir = path + "/" + fNameExt;
            check.close();
            check.open(dir, ios::binary);
        }
    }
    else
    {
        consolePrint("getHistory: " + path + " does not exist."); // throw exception in the future.
        return v_seq;
    }

    consolePrint("getHistory: " + fName + " has "
                 + std::to_string((long long)v_seq.size() - 1) + " version(s).");

    return v_seq;

}

FileSystem::StrSeq
FileSystemI::getImageList(const std::string& issue_date,const std::string& sec, const std::string& art,
                          const Ice::Current& c)
{
    using namespace std;
    using namespace FileSystem;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    std::vector<std::string> seq;
    vector<string> list;
    string dir =  main_dir + "/" + issue_date + "/" + sec + "/" + art + "/" + fs::IMAGE;
    if(!listFiles(dir,"*",list))
    {
        if(dirExists(dir))
            consolePrint("getImageList: no image found in " + dir);
        else
            consolePrint("getImageList: " + dir + "does not exist.");

        return seq;
    }

    vector<string>::const_iterator iter = list.begin();
    string prev_folder = "";
    while(iter != list.end())
    {
        string folder = extractFolderName(*iter);
        if(prev_folder.compare(folder))
            seq.push_back(folder);
        prev_folder = folder;
        iter++;
    }

    consolePrint("getImageList: " + dir + " has "
                 + std::to_string((long long)seq.size() - 1) + " image folders.");

    return seq;
}

bool
FileSystemI::changeDir(const std::string& issue_date, const std::string &sec,
                       const std::string &artOld, const std::string &art_new, const Ice::Current& c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string f_old =  main_dir + "/" + issue_date + "/" + sec + "/" + artOld;
    string f_new =  main_dir + "/" + issue_date + "/" + sec + "/" + art_new;

    if(dirExists(f_old))
        rename( f_old.c_str() , f_new.c_str() );
    else
    {
        consolePrint("changeDir: " + artOld + " does not exist!");
        return false;
    }

    f_old = f_new + "/" + fs::COPY + "/" + artOld;
    f_new = f_new + "/" + fs::COPY + "/" + art_new;

    if(dirExists(f_old))
        rename( f_old.c_str(), f_new.c_str());
    else
    {
        consolePrint("changeDir: no files to change!");
        return false;
    }

    string fNameExt_old = f_new + "/" + artOld + fs::extCOPY;
    string fNameExt_new = f_new + "/" + artOld + fs::extCOPY;

    int ver = 0;
    while(true)
    {
        string file_old = ver ? insertCorrectly(fNameExt_old, ver)
                            : fNameExt_old;
        string file_new = ver ? insertCorrectly(fNameExt_new, ver)
                            : fNameExt_new;

        ifstream check;
        check.open(file_old, ios::binary);
        if(check)
            rename(file_old.c_str(), file_new.c_str());
        else
            break;
        ver++;
    }

    consolePrint("changeDir: successfully changed name to " + art_new + ".");
    return true;
}

bool
FileSystemI::getCreationTime(const std::string &path, FileSystem::TimeIce& t)
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

std::string FileSystemI::insertCorrectly(const std::string& str, int n)
{
    using namespace std;

    const char* num = std::to_string((long long)n).c_str();

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
    return str.substr(0,iter - str.begin());
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

//std::string FileSystemI::getfName(const std::string& s)
//{
//    using namespace std;

//    string str = s;

//    string::const_iterator iter = str.begin();
//    for (iter; iter != str.end(); iter++)
//    {
//        if(*iter == '*')
//            break;
//    }

//    str.resize(iter - str.begin());
//    return str;
//}

std::string FileSystemI::fixExtension(const std::string &s, const std::string &type)
{
    using namespace std;

    string ext;
    if(!type.compare(fs::COPY))
        ext = fs::extCOPY;
    else if(!type.compare(fs::IMAGE))
        ext = fs::extIMAGE;
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

std::string
FileSystemI::addExtension(const std::string &s, const std::string &type)
{
    using namespace std;

    string ext;
    if(!type.compare(fs::COPY))
        ext = fs::extCOPY;
    else if(!type.compare(fs::IMAGE))
        ext = fs::extIMAGE;
    else
        return NULL;
    return s + ext;

}


bool FileSystemI::deleteDirectory(const std::string &dir)
{
    using namespace std;

    vector<string> files;
    vector<string> folders;

    if (listFiles(dir, "*", files))
    {
        vector<string>::const_iterator it = files.begin();
        for (it; it != files.end(); it++)
        {
            if(remove(fixPath(*it).c_str()) )
            {
                cout << fixPath(*it) << endl;
                return false;
            }
        }

        getFolders(files,folders,dir);
        vector<string>::iterator iter = folders.begin();
        for (iter; iter != folders.end(); iter++)
        {
            string str = fixPath(*iter);
            wstring temp(str.begin(),str.end());
            const wchar_t *fn = temp.c_str();
            LPCTSTR folder_name = fn;

            if(!RemoveDirectory( folder_name ))
            {
                wcout << folder_name << endl;
                return false;
            }
        }

    }
    return true;
}


bool
FileSystemI::deleteArt(const std::string& issue_date,const std::string &sec,
                       const std::string &art, const Ice::Current& c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string path =  main_dir + "/" + issue_date + "/" + sec + "/" + art;

    if(deleteDirectory(path))
    {
        consolePrint("deleteArt: " + path + "successfully deleted!");
        return true;
    }
    else
    {
        if(dirExists(path))
            consolePrint("deleteArt: deletion of " + path + " unsuccessful. Manual deletion requied.");
        else
            consolePrint("deleteArt: " + path + "does not exist.");
    }
    return false;
}

bool
FileSystemI::deleteAllImages(const std::string& issue_date, const std::string &sec,
                             const std::string &art, const Ice::Current &c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string path =  main_dir + "/" + issue_date + "/" + sec + "/" + art + "/" + fs::IMAGE;

    if(deleteDirectory(path))
    {
        consolePrint("deleteAllImages: " + path + " successfully deleted!");
        return true;
    }
    else
    {
        if(dirExists(path))
            consolePrint("deleteAllImages: deletion of " + path + " unsuccessful. Manual deletion requied.");
        else
            consolePrint("deleteAllImages: " + path + "does not exist.");
    }

    return false;
}

bool
FileSystemI::deleteImage(const std::string& issue_date, const std::string &sec,
                         const std::string &art, const std::string &name, const Ice::Current &c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string path =  main_dir + "/" + issue_date + "/" + sec + "/" + art + "/" + fs::IMAGE + "/" + name;

    if(deleteDirectory(path))
    {
        consolePrint("deleteImage: " + path + "successfully deleted!");
        return true;
    }
    else
    {
        if(dirExists(path))
            consolePrint("deleteImage: deletion of " + path + " unsuccessful. Manual deletion requied.");
        else
            consolePrint("deleteImage: " + path + "does not exist.");
    }

    return false;
}

bool
FileSystemI::deleteAllCopies(const std::string& issue_date, const std::string &sec,
                             const std::string &art, const Ice::Current &c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string path =  main_dir + "/" + issue_date + "/" + sec + "/" + art + "/" + fs::COPY;

    if(deleteDirectory(path))
    {
        consolePrint("deleteAllCopies: " + path + " successfully deleted!");
        return true;
    }
    else
    {
        if(dirExists(path))
            consolePrint("deleteAllCopies: deletion of " + path + " unsuccessful. Manual deletion requied.");
        else
            consolePrint("deleteAllCopies: " + path + "does not exist.");
    }

    return false;
}

bool
FileSystemI::deleteCopyVer(const std::string& issue_date, const std::string &sec,
                           const std::string &art, const int ver, const Ice::Current &c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string path = addExtension( main_dir + "/" + issue_date + "/" + sec + "/" + art + "/" + fs::COPY + "/" + art, fs::COPY);
    path = ver ? insertCorrectly(path,ver) : path;

    if(!remove(path.c_str()))
    {
        consolePrint("deleteCopyVer: " + path + " successfully deleted.");
        return true;
    }
    else
    {
        if(dirExists(path))
            consolePrint("deleteCopyVer: deletion of " + path + " unsuccessful. Manual deletion requied.");
        else
            consolePrint("deleteCopyVer: " + path + "does not exist.");
    }

    return false;
}

bool
FileSystemI::moveArtToSection(const std::string& issue_date, const std::string &sec_old,
                              const std::string &sec_new, const std::string &art, const Ice::Current& c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string oldPath =  main_dir + "/" + issue_date + "/" + sec_old + "/" + art;
    string newPath =  main_dir + "/" + issue_date + "/" + sec_new + "/" + art;

    wstring wOldPath(oldPath.begin(), oldPath.end());
    LPCTSTR lpOldPath = wOldPath.c_str();

    wstring wNewPath(newPath.begin(), newPath.end());
    LPCTSTR lpNewPath = wNewPath.c_str();

    bool b = MoveFile(lpOldPath, lpNewPath);

    if(b)
        consolePrint("moveArtToSec: from " + oldPath + " to " + newPath + " successfull");
    else
    {
        if(dirExists(oldPath))
            consolePrint("moveArtToSec: from " + oldPath + " to " + newPath + " unsuccessful");
        else
            consolePrint("moveArtToSec: failed. " + oldPath + " is not valid." );
    }

    return b;
}

bool FileSystemI::archiveIssue(const std::string &issue_date, const Ice::Current &c)
{
    using namespace std;

    string caller_info = getName(getIP(c));
    consolePrint("===" + caller_info + "===" );

    string oldPath =  main_dir + "/" + issue_date;
    string newPath = arc_dir;

    wstring wOldPath(oldPath.begin(), oldPath.end());
    LPCTSTR lpOldPath(wOldPath.c_str());

    wstring wNewPath(newPath.begin(), newPath.begin());
    LPCTSTR lpNewPath(wNewPath.c_str());

    bool b = MoveFile(lpOldPath, lpNewPath);

    if(b)
        consolePrint("archiveIssue: issue " + issue_date + " archived!");
    else
    {
        if(dirExists(oldPath))
            consolePrint("archiveIssue: issue " + issue_date + " could not be archived. Consider manual archival.");
        else
            consolePrint("moveArtToSec: failed. " + issue_date + " is not a valid issue date." );
    }

    return b;
}

std::string
FileSystemI::fixPath(const std::wstring& p)
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

std::wstring
FileSystemI::wFixPath(const std::wstring& p)
{
    using namespace std;
    wstring path = p;
    wstring::iterator iter = path.begin();
    for(iter; iter != path.end(); iter++)
    {
        if(*iter == L'\\')
            *iter = L'/';
    }
    return path;
}

std::string
FileSystemI::fixPath(const std::string& p)
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

bool
FileSystemI::listFiles(std::string path, std::string mask, std::vector<std::string>& files)
{
    using namespace std;

    vector<wstring> wout;
    wstring p(path.begin(), path.end());
    wstring m(mask.begin(), mask.end());

    if(!listFiles(p,m,wout))
        return false;
    vector<wstring>::const_iterator witer = wout.begin();
    while(witer != wout.end())
    {
        wstring ws = *witer;
        string s(ws.begin(), ws.end());
        files.push_back(s);
        witer++;
    }
    return true;

}

std::string
FileSystemI::extractFolderName(const std::string &s)
{
    using namespace std;
    string ret;
    string::const_iterator it, iter = s.end() - 1;
    while(*iter != '/')
    {
        if(iter == s.begin())
            return ret;
        iter--;
    }
    iter--;
    it = iter;
    while(*it != '/')
    {
        if(it == s.begin())
            return ret;
        it--;
    }
    it++;
    return s.substr(it-s.begin(),iter-it +1);
}


bool
FileSystemI::listFiles(std::wstring path, std::wstring mask, std::vector<std::wstring>& files)
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
                    files.push_back(wFixPath(path + L"\\" + ffd.cFileName));
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

void
FileSystemI::getFolders(const std::vector<std::string> vec, std::vector<std::string>& out,
                             const std::string& m_p)
{
    using namespace std;

    string main_path = fixPath(m_p);
    vector<string>::const_iterator iter = vec.begin();
    while(iter != vec.end())
    {
        string temp = *iter;

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

bool
FileSystemI::removeFolder(const std::string& folder)
{
    using namespace std;

    wstring temp(folder.begin(), folder.end());
    const wchar_t *fn = temp.c_str();
    LPCTSTR lpFolder = fn;

    return RemoveDirectory(lpFolder) ? true : false;
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
