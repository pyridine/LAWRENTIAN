module FileSystem {
    sequence<byte> ByteSeq;

    interface File {
            ByteSeq receiveFile(string name);
            bool sendFile(string name, ByteSeq seq);
    };
};
