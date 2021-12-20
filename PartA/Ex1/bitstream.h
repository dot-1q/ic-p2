#pragma once
#include <fstream>

class BitStream{
    std::fstream fileStream;
    char operation = 0x00;
    unsigned char byteBuffer = 0x00;
    short bitCounter = 0;
    short readBitCounter = 7;
    int byteCounter = 0;
    int fileByteSize = 0;

    // Public Methods
    public: 
        BitStream(const std::string file, char op);
        void writeBit(unsigned char bit);
        void writeNBits(int n, char character);
        void writeCharArray(int n, char* charArray);
        unsigned char readBit();
        unsigned char readBit(short nbit,int nByte);
        unsigned char readNBits(int n);
        int getByteSize();
        void close();

    // Private Methods
    private:
        void setByteOnBuffer();
        void getNByteFromFile(int byte);
};
