#include "../../PartA/Ex3/Golomb.cpp"
#include <CImg.h>
#include <string>

using namespace cimg_library;
using namespace std;

class ImageCodec {
    string image;

    // default constructor
    ImageCodec(){};

    public:
        // public constructor
        ImageCodec(string fileName){
            this->image = fileName;
        }
        void convertToYUV420(string convertedImgName);
};

void ImageCodec::convertToYUV420(string convertedImgName){
    // Image to transform
    CImg<unsigned char> image(this->image.c_str());

    // Get width and height
    int width = image.width();
    int height = image.height();

    // Image converted to YUV 420 with the same dimensions 
    CImg<unsigned char> imgYUV(width,height,1,3);

    for (int row = 0; row < height; row++){
        for (int column = 0; column < width; column++){
            int r = (int)image(column,row,0,0); 
            int g = (int)image(column,row,0,1); 
            int b = (int)image(column,row,0,2); 

            int y = (int) ((0.2990 * r) + (0.5870 * g) + (0.1140 * b));
            int u = (int) ((-0.1684 * r) - (0.3316 * g) + (0.5 * b) + 128);
            int v = (int) ((0.5 * r) - (0.4187 * g) - (0.0813 * b) + 128);

            if(column % 2 == 0){
                // (y,u,0)
                if(row % 2 == 0){
                    imgYUV(column,row,0,0) = y;
                    imgYUV(column,row,0,1) = u;
                    imgYUV(column,row,0,2) = 0;
                }
                // (y,0,v)
                else{
                    imgYUV(column,row,0,0) = y;
                    imgYUV(column,row,0,1) = 0;
                    imgYUV(column,row,0,2) = v;
                }
            }
            //(y,0,0)
            else{
                imgYUV(column,row,0,0) = y;
                imgYUV(column,row,0,1) = 0;
                imgYUV(column,row,0,2) = 0; 
            }
        }
    }

    imgYUV.save(convertedImgName.c_str());
    cout << "DONE" << endl;
}
