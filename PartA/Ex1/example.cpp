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

    bs.writeBit('0');
    bs.writeBit('1');
    bs.writeBit('0');
    bs.writeBit('0');
    bs.writeBit('0');
    bs.writeBit('0');
    bs.writeBit('0');
    bs.writeBit('1');
    bs.close();

    BitStream bs2("teste.bits",'r');

    
    char out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;

    cout << "New word " << endl;
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    out = bs2.readBit();
    cout  << out << endl;
    bs2.close();
}
