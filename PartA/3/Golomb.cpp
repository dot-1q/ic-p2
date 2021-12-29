#include <math.h>
#include <iostream>
#include <string>
#include <bitset>
#include "Golomb.h"

using namespace std;

Golomb::Golomb(int m){
    this->m = m;
};

string Golomb::encodeNumber(int num){
    
    // POSITIVE NUMBERS ARE MAPPED TO 2x-1
    // NEGATIVE NUMBERS ARE MAPPED TO -2x
    string code;
    if (num < 0) 
    {
        code = getCode(num*(-2),this->m); 
    }
    else 
    {
       code = getCode((num*2)-1,this->m); 
    }
    
    return code;
}

int Golomb::decodeNumber(string codeword){
    int number = decodeCode(codeword);

    // Since we map positive and negative integers, we know that
    // even encoded numbers were negative, and odd ones are 
    // positive

    if(number % 2 == 0)
    {
        return (number/-2);
    }
    else 
    {
        return ((number+1)/2); 
    }
}

string Golomb::getCode(int num, int m){
    // calc the q part
    int q = floor(num / m);
    // calc the r part
    int r = num - (q * m);
        
    // calc ceil(log2(m))
    int logCeil = ceil(log(m) / log(2));
    int numBits = pow(2, logCeil) - m;

    // creating the codeword
    string codeword = "";
    if(q == 0){
        codeword = "0";
    }
    else{
        // q represents the number of 1's
        for(int k = 0; k < q; k++){
            codeword = codeword + "1";
        }
        // add a zero at the end
            codeword = codeword + "0";
    }

    string tmp = "";
    tmp = decToBinary(r);
    if (tmp.size() < logCeil ){
        int add = logCeil - tmp.size();
        for(int j = 0; j < add; j++){
            tmp = "0" + tmp;
        }
    }

    // PARA JÁ , ASSUMIMOS QUE O M APENAS PODE SER POTENCIA DE 2
    // O QUE IMPOE UM NUMERO FIXO PARA OS BITS DE R
    codeword = codeword + tmp;
    // return golomb code
    return codeword;
}

int Golomb::decodeCode(string codeword){
    int index = 0, r;
    
    // Calc ceil(log2(m))
    int logCeil = ceil(log(this->m) / log(2));
    int numBits = pow(2, logCeil) - this->m;
    
    // Counting the number of 1's
    while (codeword[index] == '1'){
        index++;
    }   
    // q represents the number of 1's 
    int q = index;
    
    string str = codeword.substr(index, codeword.length());

    // Convert the binary substring to decimal
    int numFromBin = Golomb::binToDec(stoll(str));
    
    if(str.size() > numBits){
        r = numFromBin - numBits;
    }
    else{
        r = numFromBin;
    }

    // Calculate the final number
    int num = q * this->m + r;
    return num;
}

// Function to convert decimal to binary
string Golomb::decToBinary(int number){
    string bin = "";
    // array to store binary number
    int binaryNum[32];
 
    if (number == 0){
        return "0";
    }
    
    // counter for binary array
    int i = 0;
    while (number > 0) {
        // storing remainder in binary array
        binaryNum[i] = number % 2;
        number = number / 2;
        i++;
    }
 
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--){
        bin = bin + to_string(binaryNum[j]);
    }

    return bin;
}

// Binary code to decimal
int Golomb::binToDec(long long n) {
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }

  return dec;
}
