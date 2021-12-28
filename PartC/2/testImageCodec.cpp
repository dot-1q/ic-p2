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

    // Note that a quantization of more than 2 bits 
    // results in an image really really dark
    codec.lossyJPEG(img,"outResidual/monarchRes1",5,32,2,2,2);
    codec.lossyJPEG(img,"outResidual/monarchResY2",5,32,2,0,0);
    codec.lossyJPEG(img,"outResidual/monarchResU2",5,32,0,4,0);
    codec.lossyJPEG(img,"outResidual/monarchResV2",5,32,0,0,4);
    std::cout << "RESIDUALS DONE" << std::endl;
    
    codec.decompressImage("outResidual/monarchRes1", "outImage/lossyDecomp.ppm", 32);
    codec.decompressImage("outResidual/monarchResY2", "outImage/lossyDecompY2.ppm", 32);
    codec.decompressImage("outResidual/monarchResU2", "outImage/lossyDecompU2.ppm", 32);
    codec.decompressImage("outResidual/monarchResV2", "outImage/lossyDecompV2.ppm", 32);
    std::cout << "DECOMPRESSING DONE" << std::endl;

}


