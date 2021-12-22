#include <CImg.h>
#include "imageCodec.cpp"

using namespace cimg_library;
using namespace std;

int main(){
    ImageCodec codec = ImageCodec("monarch.ppm");
    codec.convertToYUV420("monarchYUV420.ppm");

    CImg<unsigned char> img("monarchYUV420.ppm");
    CImg<unsigned char> imgPredicted = codec.losslessJPEG(img);
    imgPredicted.save("predictedImage.ppm");
}