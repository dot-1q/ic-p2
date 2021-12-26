#include <CImg.h>
#include "imageCodec.cpp"

using namespace cimg_library;
using namespace std;

int main(){
    ImageCodec codec = ImageCodec("monarch.ppm");
    CImg<unsigned char> imgYUV420 = codec.convertToYUV420();
    imgYUV420.save("monarchYUV420.ppm");
    cout << "CONERSION DONE" << endl;

    CImg<unsigned char> img("monarchYUV420.ppm");
    CImg<unsigned char> imgPredicted = codec.losslessJPEG(img);
    imgPredicted.save("predictedImage.ppm");
    cout << "PREDICTION DONE" << endl;

    CImg<unsigned char> errorImg = codec.predictionError();
    errorImg.save("errorImage.ppm");
    cout << "ERROR IMAGE DONE" << endl;

    codec.entropyCoding("errorImage.ppm", "outputInfo.txt");
    cout << "ENTROPY CODING DONE" << endl;
}