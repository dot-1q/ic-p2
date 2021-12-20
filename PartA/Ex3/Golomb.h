#pragma once
#include <string>

class Golomb{
    // Public methods
    public:
        int m;
        std::string encodeNumber(int num);
        int decodeNumber(std::string codeword);

        // public constructor
        Golomb(int m);

        Golomb();

    // Private Methods
    private:
        std::string getCode(int num, int m);
        int decodeCode(std::string codeword);
        std::string decToBinary(int number);
        int binToDec(long long n);
};
