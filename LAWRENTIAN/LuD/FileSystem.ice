module FileSystem {
        sequence<byte> ByteSeq;
        sequence<string> StringSeq;
        struct FileInfo {
            ByteSeq bs;
            StringSeq ss;
        };
        interface File {
                FileInfo receiveFile(string name);
                void sendFile(FileInfo file);
        };
};
