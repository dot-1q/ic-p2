#include "CImg.h"
#include "ImageCodec.cpp"

using namespace cimg_library;

int main(){

    ImageCodec codec = ImageCodec("monarch.ppm");

    CImg<unsigned char> imgYUV420 = codec.convertToYUV420();
    imgYUV420.save("outImage/monarchYUV420.ppm");
    std::cout << "CONVERSION DONE" << std::endl;

    CImg<unsigned char> img("outImage/monarchYUV420.ppm");
    codec.losslessJPEG(img,"outResidual/monarchRes1",1,128);
    codec.losslessJPEG(img,"outResidual/monarchRes2",2,128);
    codec.losslessJPEG(img,"outResidual/monarchRes3",3,128);
    codec.losslessJPEG(img,"outResidual/monarchRes4",4,128);
    codec.losslessJPEG(img,"outResidual/monarchRes5",5,128);
    codec.losslessJPEG(img,"outResidual/monarchRes6",6,128);
    std::cout << "RESIDUALS DONE" << std::endl;



    codec.losslessDecompression("outResidual/monarchRes1","outImage/decompressed1.ppm",128);
    codec.losslessDecompression("outResidual/monarchRes2","outImage/decompressed2.ppm",128);
    codec.losslessDecompression("outResidual/monarchRes3","outImage/decompressed3.ppm",128);
    codec.losslessDecompression("outResidual/monarchRes4","outImage/decompressed4.ppm",128);
    codec.losslessDecompression("outResidual/monarchRes5","outImage/decompressed5.ppm",128);
    codec.losslessDecompression("outResidual/monarchRes6","outImage/decompressed6.ppm",128);
    std::cout << "DECOMPRESSING DONE" << std::endl;

}
