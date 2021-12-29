#include "../1/CImg.h"
#include "../1/ImageCodec.h"
#include <iostream>
#include <chrono>

using namespace cimg_library;


int main(){

    ImageCodec codec1 = ImageCodec("images/monarch.ppm");
    ImageCodec codec2 = ImageCodec("images/tulips.ppm");
    ImageCodec codec3 = ImageCodec("images/baboon.ppm");

    CImg<unsigned char> monarchYUV420 = codec1.convertToYUV420();
    CImg<unsigned char> tulipsYUV420 = codec2.convertToYUV420();
    CImg<unsigned char> baboonYUV420 = codec3.convertToYUV420();
    monarchYUV420.save("outImage/monarchYUV420.ppm");
    tulipsYUV420.save("outImage/tulipsYUV420.ppm");
    baboonYUV420.save("outImage/baboonYUV420.ppm");
    std::cout << "CONVERSION DONE" << std::endl;

    CImg<unsigned char> img1("outImage/monarchYUV420.ppm");
    CImg<unsigned char> img2("outImage/tulipsYUV420.ppm");
    CImg<unsigned char> img3("outImage/baboonYUV420.ppm");

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    codec1.losslessJPEG(img1,"outResidual/monarchRes",5,128);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for encoding monarch.ppm = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec2.losslessJPEG(img2,"outResidual/tulipsRes",5,128);
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for encoding tulips.ppm = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;
    
    begin = std::chrono::steady_clock::now();
    codec3.losslessJPEG(img3,"outResidual/baboonRes",5,128);
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for encoding baboon.ppm = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    std::cout << "RESIDUALS DONE" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec1.decompressImage("outResidual/monarchRes", "outImage/monarchDecomp.ppm", 128);
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for decompressing monarch.ppm = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec2.decompressImage("outResidual/tulipsRes", "outImage/tulipsDecomp.ppm", 128);
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for decompressing tulips.ppm = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec3.decompressImage("outResidual/baboonRes", "outImage/baboonDecomp.ppm", 128);
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for decompressing baboon.ppm = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;

    std::cout << "DECOMPRESSING DONE" << std::endl;

}


