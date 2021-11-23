#include <cstdio>
#include <iostream>
#include <limits>
#include <fstream>

using namespace std;

class BitStream 
{
    fstream fileStream;
    char byteBuffer = 0x00;
    int bitCounter = 0;
    int byteCounter = 0;
    int fileByteSize=0;
    
    public:
    BitStream(const string &file, char op)
    {
        if (op == 'r')
        {
            this->fileStream.open(file,ios::in);
            this->fileStream.ignore( std::numeric_limits<std::streamsize>::max() );
            fileByteSize = this->fileStream.gcount();
            this->fileStream.clear();   //  Since ignore will have set eof.
            this->fileStream.seekg( 0, std::ios_base::beg );
        }
        else if (op == 'w')
        {
            this->fileStream.open(file,ios::out);
        }
        else{
            cout << " MODO DE UTILIZAÇÂO: BitStream('filename','r/w')" << endl;
        }

    };
    public:
        void writeBit(unsigned char bit);
        unsigned char readBit();
        void writeNBits(unsigned char buffer);
        unsigned char readNBits();
        void setByteOnBuffer();
        void close();
};

void BitStream::writeBit(unsigned char bit)
{
    if (bit == '0') 
    {
        this->byteBuffer = this->byteBuffer << 1;
        this->bitCounter++;
    }
    else 
    {
        this->byteBuffer = (this->byteBuffer << 1 ) | 0x1;
        this->bitCounter++;
    }
    if(bitCounter == 8){
        this->fileStream << byteBuffer;
        this->bitCounter=0;
    } 
}

unsigned char BitStream::readBit()
{
    setByteOnBuffer();
    char out = (this->byteBuffer >> this->bitCounter) & 0x01;
    this->bitCounter++;
    if(this->bitCounter==8)
    {
        this->bitCounter = 0; 
        this->byteCounter++;
    }
    if (out==0x00) 
    {
        return '0';
    }else 
    {
        return '1';
    }
}

void BitStream::writeNBits(unsigned char buffer)
{
}

unsigned char BitStream::readNBits()
{    
}

void BitStream::setByteOnBuffer()
{
    this->byteBuffer = fileStream.get();
    fileStream.seekg(this->byteCounter);
}

void BitStream::close()
{
    cout << "Closing File" << endl;
    this->fileStream.close();
}
