#include <iostream>
#include <math.h>
#include <string>
using namespace std;

class Golomb{
    int m;
    int q;
    int r;
    string codeword;

    // private constructor
    Golomb(int q, int r, string codeword){
        this->q = q;
        this->r = r;
        this->codeword = codeword;
    };

    // default constructor
    Golomb(){};

    public:
        void encodeNumbers(int *nums, int size);
        Golomb* decodeNumbers(int nums[]);
        string getInfo();
        string decToBinary(int n);

        // public constructor
        Golomb(int m){
            this->m = m;
        };
};

void Golomb::encodeNumbers(int *nums, int size){
    Golomb golombCodes[size];

    for(int i = 0; i < size; i++){
        // num should be greater or equal to zero
        if(nums[i] >= 0){
            // calc the q part
            int q = floor(nums[i] / this->m);
            // calc the r part
            int r = nums[i] - (q * this->m);

            // calc ceil(log2(m))
            int logCeil = ceil(log(this->m) / log(2));
            int numBits = pow(2, logCeil) - this->m;

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

            // pass the r value to binary code
            string tmp = "";
            if(r < numBits){
                tmp = Golomb::decToBinary(r);
            }
            else{
                tmp = Golomb::decToBinary(r+numBits);
            }

            if (tmp.size() < (numBits - 1) ){
                int add = (numBits-1) - tmp.size();
                for(int j = 0; j < add; j++){
                    tmp = "0" + tmp;
                }
            }
            codeword = codeword + tmp;

            // create the corresponding golomb object type 
            Golomb code = Golomb(q,r,codeword);
            // ad the object to the array of golomb codes
            golombCodes[i] = code;
        }
        else{
            cout << "ERROR!! The number inserted should be greater or equal to zero!" << endl;
        }
    }

    for(int i = 0; i < size; i++){
        cout << "i: "<< i << " | " << golombCodes[i].getInfo() << endl;
    }
}

// function to convert decimal to binary
string Golomb::decToBinary(int n){
    string bin = "";
    // array to store binary number
    int binaryNum[32];
 
    if (n == 0){
        return "0";
    }
    
    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
 
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--){
        bin = bin + to_string(binaryNum[j]);
    }

    return bin;
}

// to print the info about the object
string Golomb::getInfo(){
    return "q: " + to_string(this->q) + " |  r: " + to_string(this->r) + " | codeword: " + this->codeword;
}