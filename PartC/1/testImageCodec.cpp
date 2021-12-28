#include "../1/CImg.h"
#include "../1/ImageCodec.h"
#include <iostream>

using namespace cimg_library;


int main(){

    ImageCodec codec = ImageCodec("monarch.ppm");

    CImg<unsigned char> imgYUV420 = codec.convertToYUV420();
    imgYUV420.save("outImage/monarchYUV420.ppm");
    std::cout << "CONVERSION DONE" << std::endl;

    CImg<unsigned char> img("outImage/monarchYUV420.ppm");
    codec.losslessJPEG(img,"outResidual/monarchRes1",2,128);
    std::cout << "RESIDUALS DONE" << std::endl;
    
    codec.decompressImage("outResidual/monarchRes1", "outImage/lossyDecomp.ppm", 128);
    std::cout << "DECOMPRESSING DONE" << std::endl;

}


