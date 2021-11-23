#include "bitstream.cpp"

int main()
{
    BitStream bs("teste.bits",'w');
    bs.writeBit('0');
    bs.writeBit('0');
    bs.writeBit('1');
    bs.writeBit('0');
    bs.writeBit('0');
    bs.writeBit('0');
    bs.writeBit('1');
    bs.writeBit('1');
}
