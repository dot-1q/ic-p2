#pragma once
#include <string>
using namespace std;

class Golomb{
    // Public methods
    public:
        int m;
        string encodeNumber(int num);
        int decodeNumber(string codeword);

        // public constructor
        Golomb(int m);

        Golomb();

    // Private Methods
    private:
        string getCode(int num, int m);
        int decodeCode(string codeword);
        string decToBinary(int number);
        int binToDec(long long n);
};