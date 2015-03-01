module FileSystem {
    const string COPY = "Copy";
    const string IMAGE = "Image";
    const string extCOPY = ".docx";
    const string extIMAGE = ".jpg";

    sequence<byte> ByteSeq;
    struct TimeIce {
        string dayOfTheWeek;
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        int milliseconds;
    };
    struct Version{
        int verNum;
        string verName;
        TimeIce time;
    };
    sequence<Version> VerSeq;
    sequence<string> StrSeq;
    interface File {
        ByteSeq receiveLatest(string issueDate, string sec, string art, string type, string fName);
        ByteSeq receiveVersion(string issueDate,string sec, string art, string type, string fName, int ver);

        bool sendFile(string issueDate,string sec, string art, string type, string fNameExt, ByteSeq seq);

        VerSeq getHistory(string issueDate,string sec, string art, string type, string fName);
        StrSeq getImageList(string issueDate,string sec, string art);

        bool renameArt(string issueDate,string sec, string artOld, string artNew);
        bool changeArtSection(string issueDate,string secOld, string secNew, string art);
        bool changeArtIssueDate(string oldIssueDate, string newIssueDate, string sec, string art);
        bool archiveIssue(string issueDate);

        bool deleteArt(string issueDate,string sec, string art);
        bool deleteAllImages(string issueDate,string sec, string art);
        bool deleteImage(string issueDate,string sec, string art, string name);
        bool deleteAllCopies(string issueDate,string sec, string art);
        bool deleteCopyVer(string issueDate,string sec, string art, int ver);
    };
};

module fs {
    const string COPY = "Copy";
    const string IMAGE = "Image";
    const string extCOPY = ".docx";
    const string extIMAGE = ".jpg";
};
