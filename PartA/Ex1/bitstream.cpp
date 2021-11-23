#include <iostream>
#include <fstream>

using namespace std;

class BitStream 
{
    fstream fileStream;
    char byteBuffer = 0x00;
    int bitCounter = 0;
    
    public:
    BitStream(const string &file, char op)
    {
        if (op == 'r')
        {
            this->fileStream.open(file,ios::in);
        }
        else if (op == 'w')
        {
            this->fileStream.open(file,ios::out);
        }
        else
        {
            cout << " MODO DE UTILIZAÇÂO: BitStream('filename','r/w')" << endl;
        }

    };
    public:
        void writeBit(unsigned char bit);
        unsigned char readBit();
        void writeNBits(unsigned char buffer);
        unsigned char readNBits();
};

void BitStream::writeBit(unsigned char bit)
{
    if (bit == '0') 
    {
        this->byteBuffer = this->byteBuffer << 1;
        bitCounter++;
    }
    else 
    {
        this->byteBuffer = this->byteBuffer << 1;
        this->byteBuffer = this->byteBuffer | 0x1;
        bitCounter++;
    }
    if(bitCounter == 8) this->fileStream << byteBuffer << endl;
}

unsigned char BitStream::readBit()
{
}

void BitStream::writeNBits(unsigned char buffer)
{
}

unsigned char BitStream::readNBits()
{    
}
