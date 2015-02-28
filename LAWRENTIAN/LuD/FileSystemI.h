#ifndef FILESYSTEMI_H
#define FILESYSTEMI_H

#include <Ice/Ice.h>
#include "FileSystem.h"
#include <Windows.h>

struct Time_t{
    std::string dayOfTheWeek;
    std::string day;
    std::string month;
    std::string year;
    std::string hour;
    std::string minute;
    std::string second;
    std::string milliseconds;
};


class FileSystemI : public FileSystem::File
{
private:
    std::string arc_dir;
    std::string main_dir;
    bool getCreationTime(const std::string& path, FileSystem::TimeIce& time);
    bool dirExists(const std::string& dirName_in);
    std::string extractFileName(const std::string& str);
    std::string extractNodeName(const std::string str);
    std::string insertCorrectly(const std::string& str, int num);
    std::string getIP(const Ice::Current& c);
    void consolePrint(const std::string& str);
    std::string getName(const std::string& ip_address);
    std::string addExtension(const std::string &s, const std::string &type);
//    std::string getfName(const std::string& s);
    std::string fixExtension(const std::string& s, const std::string& type);
    void getFolders(const std::vector<std::string> vec, std::vector<std::string>& out,
               const std::string& m_p);
    bool listFiles(std::wstring path, std::wstring mask, std::vector<std::wstring>& files);
    std::string fixPath(const std::string& p);
    std::string fixPath(const std::wstring& p);
    bool deleteDirectory(const std::string &dir);
    bool listFiles(std::string path, std::string mask, std::vector<std::string>& files);
    std::string extractFolderName(const std::string& s);
    std::wstring wFixPath(const std::wstring& p);
    bool FileSystemI::removeFolder(const std::string& folder);

public:
    FileSystemI(std::string main_node);
    FileSystemI();

    virtual FileSystem::ByteSeq
    receiveLatest(const std::string& issueDate, const std::string& sec, const std::string& art,
                  const std::string& type, const std::string& fName,
                  const Ice::Current& c);

    virtual FileSystem::ByteSeq
    receiveVersion(const std::string& issueDate,const std::string& sec, const std::string& art,
                   const std::string& type, const std::string& fName,
                   const int ver, const Ice::Current& c);

    virtual bool
    sendFile(const std::string& issueDate,const std::string& sec, const std::string& art,
             const std::string& type, const std::string& fNameExt,
             const FileSystem::ByteSeq& seq, const Ice::Current& c);

    virtual FileSystem::VerSeq
    getHistory(const std::string& issueDate,const std::string& sec, const std::string& art,
             const std::string& type, const std::string& fName,
             const Ice::Current& c);

    virtual FileSystem::StrSeq
    getImageList(const std::string& issueDate,const std::string& sec, const std::string& art,
                 const Ice::Current& c);

    virtual bool
    changeDir(const std::string& issueDate,const std::string& sec, const std::string& artOld,
              const std::string& art_new, const Ice::Current& c);

    virtual bool
    deleteArt(const std::string& issueDate,const std::string& sec, const std::string& art,
              const Ice::Current& c);

    virtual bool
    deleteAllImages(const std::string& issueDate,const std::string& sec, const std::string& art,
                    const Ice::Current& c);

    virtual bool
    deleteImage(const std::string& issueDate,const std::string& sec, const std::string& art,
                const std::string& name, const Ice::Current& c);

    virtual bool
    deleteAllCopies(const std::string& issueDate,const std::string& sec, const std::string& art,
                    const Ice::Current& c);

    virtual bool
    deleteCopyVer(const std::string& issueDate,const std::string& sec, const std::string& art,
                  const int ver, const Ice::Current& c);

    virtual bool
    moveArtToSection(const std::string& issueDate,const std::string& secOld, const std::string& secNew,
                 const std::string& art, const Ice::Current& c);

    virtual bool
    archiveIssue(const std::string& issueDate, const Ice::Current& c);

};

#endif // FILESYSTEMI_H
