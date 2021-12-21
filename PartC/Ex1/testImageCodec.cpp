#include <CImg.h>
#include "imageCodec.cpp"

using namespace cimg_library;
using namespace std;

int main(){
    ImageCodec codec = ImageCodec("monarch.ppm");
    codec.convertToYUV420("newImage.ppm");
}