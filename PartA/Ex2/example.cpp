#include "../Ex1/bitstream.cpp"

using namespace std;

int main()
{
    BitStream bs("teste.bits",'w');
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(1);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(1);
    bs.writeBit(1);

    bs.writeBit(0);
    bs.writeBit(1);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(0);
    bs.writeBit(1);
    bs.close();

    BitStream bs2("teste.bits",'r');
    
    char out = bs2.readBit();
    cout  << (short)out << std::endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;

    cout << "New word " << endl;
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    out = bs2.readBit();
    cout  << (short)out << endl;
    bs2.close();



    char array[5] = {'a','b','c','d','e'};

    BitStream bs3("nbits.bits",'w');
    for(int i = 0; i< 5; i++)
    {
        bs3.writeNBits(3,array[i]);
    }
    bs3.close();

    BitStream bs4("chararray.bits",'w');
    bs4.writeCharArray(5, array);
    bs4.close();


    BitStream bs5("chararray.bits",'r');
    bs5.readNBits(5);
    bs5.close();

    BitStream bs6("chararray.bits",'r');
    cout << (short) bs6.readBit(8,0);
    cout << (short) bs6.readBit(7,0);
    cout << (short) bs6.readBit(6,0);
    bs6.close();
}
