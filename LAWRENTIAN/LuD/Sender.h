#ifndef SENDER_H
#define SENDER_H

#include <Ice/Ice.h>
#include "FileSystem.h"
#include <fstream>
#include <string>

class Sender
{
    Ice::CommunicatorPtr ic;
    FileSystem::FilePrx fpx;
public:
    // Just use thise constructor
    Sender();
    Sender(const std::string& connection);
    Sender(const int& num);
    ~Sender();

    /*! \brief sendCopy: sends an article from client to server provided file is lesser than 1MB.
     *
     *  \param issueDate: the deadline date of the issue which the article belongs to.
     *  \param sec: the section to which the article belongs to.
     *  \param art: name of the article.
     *  \param type: either fs::COPY or fs::IMAGE. Don't forget #include "FileSystem.h".
     *  \param clDir: full file path of the file to be sent.
     *  \return true if file successfuly sent, false otherwise.
     */
    bool sendCopy(const std::string& issueDate, const std::string& sec, const std::string& art, const std::string& type, const std::string& clDir);
    /*! \brief sendImage: sends an image from client to server provided file is lesser than 1MB.
     *
     *  \param issueDate: the deadline date of the issue which the article belongs to.
     *  \param sec: the section to which the article belongs to.
     *  \param art: name of the article.
     *  \param type: either fs::COPY or fs::IMAGE. Don't forget #include "FileSystem.h".
     *  \param fName: name of file saved in server.
     *  \param clDir: full file path of the file to be sent.
     *  \return true if file successfuly sent, false otherwise.
     */
    bool sendImage(const std::string& issueDate, const std::string& sec, const std::string& art, const std::string& type, const std::string& fName, const std::string& clDir);

    /*! \brief requestFile: request any file (article or image) from server and download to client, provided that
     *         file is lesser than 1MB and exists in server.
     *
     *  \param issueDate: the deadline date of the issue which the article belongs to.
     *  \param sec: the section to which the article belongs to.
     *  \param art: name of the article.
     *  \param type: either fs::COPY or fs::IMAGE. Don't forget #include "FileSystem.h".
     *  \param down_dir: full folder path to where the file will be downloaded.
     *  \param ver: [opt] version of file, default -1. If ver = -1, highest version file is received.
     *              If ver = 0, lowest version file is received.
     *  \return true if file successfuly downloaded, false otherwise.
     */
    bool requestFile(const std::string& issueDate, const std::string& sec, const std::string& art, const std::string& type, const std::string& down_dir, int ver = -1);
    /*!
     * \brief getHistory: gets the different versions of a file along with each creation date in the server.
     * \param issueDate: the deadline date of the issue which the article belongs to.
     * \param sec: the section to which the article belongs to.
     * \param art: name of the article.
     * \param type: either fs::COPY or fs::IMAGE. Don't forget #include "FileSystem.h".
     * \return a VerSeq object, which is a vector<Version> object. A Version object is a struct which contains
     *         verName, verNum, and verTime information. verTime is an obect which is also a struct which contains
     *         dayOfTheWeek, year, month, day, hour, minute, second, millisecond information of file.
     */
    FileSystem::VerSeq getHistory(const std::string& issueDate, const std::string& sec, const std::string& art, const std::string& type);
    /*!
     * \brief getImageList: gets a list of image names from server for a particular article in the server.
     * \param issueDate: the deadline date of the issue which the article belongs to.
     * \param sec: the section to which the article belongs to.
     * \param art: name of the article.
     * \return a StrSeq object which is a vector<string> object of the different image names.
     */
    FileSystem::StrSeq getImageList(const std::string& issueDate, const std::string& sec, const std::string& art);
    /*!
     * \brief renameArticle: renames an existing article in the server.
     * \param issueDate: the deadline date of the issue which the article belongs to.
     * \param sec: the section to which the article belongs to.
     * \param artOld: name of the article to change.
     * \param artNew: new name for the article to change to.
     * \return true if rename successfull and false otherwise.
     */
    bool renameArticle(const std::string& issueDate,const std::string& sec, const std::string& artOld, const std::string& artNew);
    /*!
     * \brief changeArtSection: moves specified article from current section to specified section in the server. Useful if section value changes.
     * \param issueDate: the deadline date of the issue which the article belongs to.
     * \param secOld: the section to which the article to be moved belongs to.
     * \param secNew: the section to which the article will be moved to.
     * \param art: name of the article.
     * \return true if successfully renamed and false otherwise.
     */
    bool changeArtSection(const std::string& issueDate,const std::string& secOld, const std::string& secNew, const std::string& art);
    /*!
     * \brief archiveIssue: archives the specified issue in the server.
     * \param issueDate: the deadline date of the issue which the article belongs to.
     * \return true if issue has been successfully moved and false otherwise.
     */
    bool archiveIssue(const std::string& issueDate);
    /*!
     * \brief deleteArt: deletes the specified article in the server.
     * \param issueDate: the deadline date of the issue which the article belongs to.
     * \param sec: the section to which the article belongs to.
     * \param art: name of the article.
     * \return true if issue has been successfully archived and false otherwise.
     */
    bool deleteArt(const std::string& issueDate,const std::string& sec, const std::string& art);
    /*!
     * \brief deleteAllImages: deletes 'Image' folder belonging to the specified article.
     * \param issueDate: the deadline date of the issue which the article belongs to.
     * \param sec: the section to which the article belongs to.
     * \param art: name of the article.
     * \return true if 'Image' folder has been succeessfully deleted and false otherwise.
     */
    bool deleteAllImages(const std::string& issueDate,const std::string& sec, const std::string& art);
    /*!
     * \brief deleteImage: deletes the specified image.
     * \param issueDate: the deadline date of the issue of the article which the image belongs to.
     * \param sec: the section of the article to which the image belongs to.
     * \param art: name of the article to which the image belongs to.
     * \param name: name of image to delete.
     * \return true if specified image deleted and false otherwise.
     */
    bool deleteImage(const std::string& issueDate,const std::string& sec, const std::string& art, const std::string& name);
    /*!
     * \brief deleteAllCopies: deletes the entiry 'Copy' folder in the specified article.
     * \param issueDate: the deadline date of the issue which the article belongs to.
     * \param sec: the section to which the article belongs to.
     * \param art: name of the article.
     * \return true if 'Copy' folder has been succeessfully deleted and false otherwise.
     */
    bool deleteAllCopies(const std::string& issueDate, const std::string& sec, const std::string& art);
    /*!
     * \brief deleteCopyVer: deletes a particular copy version and renames the files to reflect the change.
     * \param issueDate: the deadline date of the issue which the article belongs to.
     * \param sec: the section to which the article belongs to.
     * \param art: name of the article.
     * \param ver:[opt] version of copy to be deleted. ver = -1 by default. If ver = -1, the highest version is deleted.
     *        If ver = 0, the lowest version is deleted.
     * \return true if deletion was successful and false otherwise.
     */
    bool deleteCopyVer(const std::string& issueDate,const std::string& sec, const std::string art, int ver = -1);

    /*!
     * \brief changeArtIssueDate: puts the article in the oldIssueDate folder to the newIssueDate folder in the server.
     * \param oldIssueDate: the issue date to which the article currently belongs.
     * \param newIssueDate: the issue date which the article will change to.
     * \param sec: the section to which the article belongs to.
     * \param art: name of the article.
     * \return true if change was successful and false otherwise.
     */
    bool changeArtIssueDate(const std::string& oldIssueDate, const std::string& newIssueDate, const std::string& sec, const std::string& art);
};

#endif // SENDER_H
