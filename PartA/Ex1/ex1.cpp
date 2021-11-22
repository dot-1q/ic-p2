#include <iostream>
#include <fstream>

using namespace std;

class BitStream {
    FILE* file;

    BitStream(const char* file, const char* op){
        if (*op == 'r'){
            this->file = fopen(file, op);
        }
        else if (*op == 'w'){
            this->file = fopen(file, op);
        }
        else{
            cout << "NÃO SE USA ASSIM BURRO!!" << endl;
        }

    };

    public:
        void writeBit(unsigned char bit);
        unsigned char readBit();
        void writeNBits(unsigned char buffer);
        unsigned char readNBits();
};

void BitStream::writeBit(unsigned char bit){
    this->f << bit << endl;
}

unsigned char BitStream::readBit(){

}

void BitStream::writeNBits(unsigned char buffer){

}

unsigned char BitStream::readNBits(){
    
}