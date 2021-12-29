#include "../3/Golomb.h"
#include "../1/bitstream.h"
#include <cmath>
#include <ostream>
#include <string>
#include <iostream>

std::string decodeCode(BitStream &stream, short restBits, int &n)
{
    unsigned char out;
    std::string decode="";
    out = stream.readBit();
    n++;

    while(out!=0x00)
    {
        decode = decode + '1';
        out = stream.readBit();
        n++;
    }

    decode = decode + '0';
    for(int i = 0; i<restBits;i++)
    {
        out = stream.readBit();
        if(out == 0x00) decode = decode + '0';
        if(out == 0x01) decode = decode + '1';
        n++;
    }

    return decode;
}

int main(){
    // Create golomb object with m = 5
    Golomb golombEncoder = Golomb(4);
    Golomb golombDecoder = Golomb(4);
    BitStream bs = BitStream("out.txt",'w'); 


    int nums[16] = {-20,19,3,2,-14,6,3,6,-2,0,-1,1,5,-6,8,-13};
    
    std::cout << "Numbers written on file" << std::endl;
    std::string codeword;
    for (int i=0;i<16;i++){
        codeword = golombEncoder.encodeNumber(nums[i]); 
        std::cout << "i: [" << nums[i] << "] code: " << codeword << " | " << std::endl;
        
        for(auto &ch : codeword)
        {
            if(ch == '0') bs.writeBit(0); 
            if(ch == '1') bs.writeBit(1); 
        }
    }

    bs.close();

    std::cout << "\n-------------------------------------------" << std::endl;

    std::cout << "Number (111111010) is: " << golombDecoder.decodeNumber("111111010") << std::endl;
    std::cout << "Number (1111001) is: " << golombDecoder.decodeNumber("1111001") << std::endl;
    std::cout << "Number (11111111011) is: " << golombDecoder.decodeNumber("11111111011") << std::endl;
    std::cout << "Number (1111111111000) is: " << golombDecoder.decodeNumber("1111111111000") << std::endl;
    
    std::cout << "-------------------------------------------" << std::endl;




    std::cout << "Numbers decoded from file" << std::endl;
    // DECODE PROCESS
    BitStream bd = BitStream("out.txt",'r');
    int bitsInFile = bd.getByteSize() * 8;
    short rbin = ceil(log(golombEncoder.m)/log(2));
    int bits = 0;
    std::string code;

    while(bits < bitsInFile)
    {
        code = decodeCode(bd,rbin,bits); 
        std::cout << golombDecoder.decodeNumber(code) << " | ";
    }

    bd.close();
}
