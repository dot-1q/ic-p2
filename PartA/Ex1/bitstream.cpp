#include <iostream>
#include <limits>
#include <fstream>
#include <bitset>
#include "bitstream.h"

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
    // get on the byte buffer, the correct byte from the file
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
    // out will be either 0x00 (0) or 0x01 (1)
    return out;
}

unsigned char BitStream::readBit(short nBit,int nByte)
{
    // get on the byte buffer, the correct byte from the file
    getNByteFromFile(nByte);
    // get the "nth" bit from the byte with this formula
    char out = (this->byteBuffer >> nBit) & 0x01;
    // out will be either 0x00 (0) or 0x01(1)
    return out;
}

void BitStream::writeNBits(int n, char character)
{
    for(int bit = 0; bit < n; bit++)
    {
        // get the "nth" bit from the character with this formula
        // We are writing from MSB to LSB, hence why  we mask with "0x80"
        unsigned char byteToWrite = (character << bit) & 0x80;
        // The bit is stored in the MSB of the previous variabe, so we shift it 
        // 7 places, so that the bit we care is on LSB, and call writeBit
        this->writeBit(byteToWrite>>7);
    }
}

void BitStream::writeCharArray(int n, char *charArray)
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

void BitStream::readNBits(int n)
{   
    std::cout << "\nMSB -> LSB" << std::endl;
    this->bitCounter=0;
    this->byteCounter=0;
    unsigned char out = 0x00;
    char aux = 0x00;
    for(int i = 1; i <= n; i++)
    {
        aux = this->readBit();
        if(aux==0x00)
        {
            std::cout << (short) aux;
            out = out >> 1; 
        }
        else if(aux==0x01)
        {
            std::cout << (short) aux;
            out = (out >> 1) | 0x80; 
        }
        if(i%8==0) std::cout << " is " << std::bitset<8>(out) << " : "<< out <<"\n" << std::endl;
    }
}

void BitStream::setByteOnBuffer()
{
    // seekg(n) puts the internal file pointer on the "nth" byte. This "nth" byte is updated internally as we read bit by bit 
    fileStream.seekg(this->byteCounter);
    // Get the byte from the file thats currently being read bit by bit 
    this->byteBuffer = fileStream.get();
}

void BitStream::getNByteFromFile(int byte)
{
    // seekg(n) puts the internal file pointer on the "nth" byte. This "nth" byte is updated internally as we read bit by bit 
    fileStream.seekg(byte);
    // Get the byte from the file thats currently being read bit by bit 
    this->byteBuffer = fileStream.get();
}

void BitStream::close()
{
    // If this filestream was a 'write' one, we finish the final byte
    if(this->operation=='w')
    {
        // means we have yet to complete the final byte
        if (this->bitCounter != 0) 
        {
            // check how many bits left to be written
            short bitsLeft = (8 - this->bitCounter);
            // write that ammount of bits with character 0
            this->writeNBits(bitsLeft, 0x00);
        }
    }
    std::cout << "\nClosing File" << std::endl;
    this->fileStream.close();
}
