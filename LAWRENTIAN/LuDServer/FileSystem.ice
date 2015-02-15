module FileSystem {
    sequence<byte> ByteSeq;
    struct Version{
        int verNum;
        string verName;
    };
    sequence<Version> VerSeq;
    interface File {
        ByteSeq receiveLatest(string sec, string art, string type, string fName);
        ByteSeq receiveVersion(string sec, string art, string type, string fName, int ver);
        bool sendFile(string sec, string art, string type, string fNameExt, ByteSeq seq);
        VerSeq getHistory(string sec, string art, string type, string fName);
    };
};
