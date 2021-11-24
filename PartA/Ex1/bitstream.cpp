#include <cstdio>
#include <iostream>
#include <limits>
#include <fstream>

using namespace std;

class BitStream 
{
    fstream fileStream;
    char byteBuffer = 0x00;
    short bitCounter = 0;
    int byteCounter = 0;
    int fileByteSize=0;
    
    public:
    BitStream(const string &file, char op)
    {
        if (op == 'r')
        {
            this->fileStream.open(file,ios::in);
            // Find how many bytes are in the file to be read, so that we can keep track on wich to read
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
        void writeNBits(int n, char *charArray);
        unsigned char readBit();
        void readNBits();
        void close();
    private:
        void setByteOnBuffer();
};

void BitStream::writeBit(unsigned char bit)
{
    // if the bit to be written is a 0, we simply shift the buffer one position
    if (bit == 0x00) this->byteBuffer = this->byteBuffer << 1;
    // if the bit is a 1, we shift and bitwise OR to force the LSB to be 1
    else if (bit==0x01) this->byteBuffer = (this->byteBuffer << 1 ) | 0x01;
    //increment number of bits written
    this->bitCounter++;
    // when we write a whole byte (8 bits) we write the buffer on the file
    if(bitCounter == 8)
    {
        this->fileStream << byteBuffer;
        this->bitCounter=0;
    } 
}

unsigned char BitStream::readBit()
{
    // get on the byte buffer the correct byte from the file
    setByteOnBuffer();
    // get the "nth" bit from the byte with this formula
    char out = (this->byteBuffer >> this->bitCounter) & 0x01;
    // increment the bit read
    this->bitCounter++;
    // If we've internally read 8 bits, means we've read a whole byte
    if(this->bitCounter==8)
    {
        // so we update the bitcounter variable and the byte counter accordingly 
        this->bitCounter = 0; 
        this->byteCounter++;
    }
    // out will be either 0x00 (0) or 0x01(1)
    return out;
}

void BitStream::writeNBits(int n, char *charArray)
{
    for (int i=0; i<n; i++) {
        for(int bit=0;bit<8;bit++)
        {
            // get the "nth" bit from the byte with this formula
            // We are writing from MSB to LSB, hence why  we mask with "0x80"
            unsigned char byteToWrite = (charArray[i] << bit) & 0x80;
            // The bit is stored in the MSB of the previous variabe, so we shift it 
            // 7 places, so that the bit we care is on LSB, and call writeBit
            this->writeBit(byteToWrite>>7);
        }
    }
}

void BitStream::readNBits()
{    
}

void BitStream::setByteOnBuffer()
{
    // Get the byte from the file thats currently being read bit by bit 
    this->byteBuffer = fileStream.get();
    // seekg(n) puts the internal file pointer on the "nth" byte. This "nth" byte is updated internally as we read bit by bit 
    fileStream.seekg(this->byteCounter);
}

void BitStream::close()
{
    cout << "Closing File" << endl;
    this->fileStream.close();
}
