#include <iostream>
#include "Golomb.cpp"
using namespace std;

int main(){
    // Create golomb object with m = 5
    Golomb golomb = Golomb(5);

    int nums[] = {0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6,-6,7,-7,8,-8,9,-9,10,-10};
    int size = sizeof(nums)/sizeof(nums[0]);

    for (int i=0;i<21;i++){
        cout << "i: " << nums[i] << " | " << golomb.encodeNumber(nums[i]) <<endl;
    }

    cout << "-------------------------------------------" << endl;

    cout << "Number (111000) is: " << golomb.decodeNumber("111000") << endl;
    cout << "Number (1110110) is: " << golomb.decodeNumber("1110110") << endl;
}
