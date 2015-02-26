module FileSystem {
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
    interface File {
        ByteSeq receiveLatest(string sec, string art, string type, string fName);
        ByteSeq receiveVersion(string sec, string art, string type, string fName, int ver);
        bool sendFile(string sec, string art, string type, string fNameExt, ByteSeq seq);
        VerSeq getHistory(string sec, string art, string type, string fName);
    };
};
