#include "../1/CImg.h"
#include "../1/ImageCodec.h"
#include <iostream>
#include <chrono>

using namespace cimg_library;

int main(){

    ImageCodec codec = ImageCodec("monarch.ppm");

    CImg<unsigned char> imgYUV420 = codec.convertToYUV420();
    imgYUV420.save("outImage/monarchYUV420.ppm");
    std::cout << "CONVERSION DONE" << std::endl;

    CImg<unsigned char> img("outImage/monarchYUV420.ppm");

    // Note that a quantization of more than 2 bits 
    // results in an image really really dark
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    codec.lossyJPEG(img,"outResidual/monarchRes1",5,32,2,2,2);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for Lossy 2 bits encoding monarch.ppm = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    //codec.lossyJPEG(img,"outResidual/monarchResY2",5,32,2,0,0);
    //codec.lossyJPEG(img,"outResidual/monarchResU2",5,32,0,4,0);
    //codec.lossyJPEG(img,"outResidual/monarchResV2",5,32,0,0,4);
    //std::cout << "RESIDUALS DONE" << std::endl;
    
    begin = std::chrono::steady_clock::now();
    codec.decompressImage("outResidual/monarchRes1", "outImage/lossyDecomp.ppm", 32);
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for Lossy 2 bits decompression monarch.ppm = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;
    //codec.decompressImage("outResidual/monarchResY2", "outImage/lossyDecompY2.ppm", 32);
    //codec.decompressImage("outResidual/monarchResU2", "outImage/lossyDecompU2.ppm", 32);
    //codec.decompressImage("outResidual/monarchResV2", "outImage/lossyDecompV2.ppm", 32);
    //std::cout << "DECOMPRESSING DONE" << std::endl;

    
    CImg<unsigned char> twobit("outImage/lossyDecomp.ppm");
    CImg<unsigned char> twobitY("outImage/lossyDecompY2.ppm");
    CImg<unsigned char> fourbitU("outImage/lossyDecompU2.ppm");
    CImg<unsigned char> fourbitV("outImage/lossyDecompV2.ppm");
    
    std::cout << "Two bit SNR and ERROR" << std::endl;
    codec.getSNR(img, twobit);
    std::cout << "Two bit Y channel SNR and ERROR" << std::endl;
    codec.getSNR(img, twobitY);
    std::cout << "Four bit U SNR and ERROR" << std::endl;
    codec.getSNR(img, fourbitU);
    std::cout << "Four bit V SNR and ERROR" << std::endl;
    codec.getSNR(img, fourbitV);


}
