#include <iostream>
#include "Golomb.cpp"
using namespace std;

int main(){
    Golomb golomb = Golomb(8);

    int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; 
    int size = sizeof(nums)/sizeof(nums[0]);
    int *p = nums;

    golomb.encodeNumbers(p, size);
}