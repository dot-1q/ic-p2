#include "../../PartA/Ex3/Golomb.cpp"
#include "../../PartA/Ex1/bitstream.h"
#include "CImg.h"
#include <string>
#include <cmath>
#include <iostream>

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
        CImg<unsigned char> convertToYUV420();
        CImg<unsigned char> losslessJPEG(CImg<unsigned char> image);    
        CImg<unsigned char> predictionError();
        void entropyCoding(string imgName, string fileToWrite);
};

CImg<unsigned char> ImageCodec::convertToYUV420(){
    // Image to transform
    CImg<unsigned char> image(this->image.c_str());

    // Get width and height
    int width = image.width();
    int height = image.height();

    // Image converted to YUV 420 with the same dimensions 
    CImg<unsigned char> imgYUV(width,height,1,3);

    for (int row = 0; row < height; row++){
        for (int column = 0; column < width; column++){
            // Get the RGB values from the initial image
            int r = (int)image(column,row,0,0); 
            int g = (int)image(column,row,0,1); 
            int b = (int)image(column,row,0,2); 

            // Calculate the YUV values
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
    return imgYUV;
}

CImg<unsigned char> ImageCodec::losslessJPEG(CImg<unsigned char> image){
    // Get width and height
    int width = image.width();
    int height = image.height();

    // The image with the predictions 
    CImg<unsigned char> imgPredicted(width,height,1,3);

    for (int row = 0; row < height; row++){
        for (int column = 0; column < width; column++){
            // If it's a border pixel
            if( (row == 0) || (row == height-1) || (column == 0) || (column == width-1) ){
                // The data stays the same
                imgPredicted(column,row,0,0) = image(column,row,0,0);
                imgPredicted(column,row,0,1) = image(column,row,0,1);
                imgPredicted(column,row,0,2) = image(column,row,0,2);
            }
            // If it's a inner pixel
            else{
                // To store the seven linear predictors data 
                int predictors[3][10];

                // Mode 1 -> a
                predictors[0][0] = image(column-1,row,0,0);
                predictors[1][0] = image(column-1,row,0,1);
                predictors[2][0] = image(column-1,row,0,2);

                // Mode 2 -> b
                predictors[0][1] = image(column,row-1,0,0);
                predictors[1][1] = image(column,row-1,0,1);
                predictors[2][1] = image(column,row-1,0,2);

                // Mode 3 -> c 
                predictors[0][2] = image(column-1,row-1,0,0);
                predictors[1][2] = image(column-1,row-1,0,1);
                predictors[2][2] = image(column-1,row-1,0,2);

                // Mode 4 -> a + b - c
                predictors[0][3] = predictors[0][0] + predictors[0][1] - predictors[0][2];
                predictors[1][3] = predictors[1][0] + predictors[1][1] - predictors[1][2];
                predictors[2][3] = predictors[2][0] + predictors[2][1] - predictors[2][2];

                // Mode 5 -> a + (b - c) / 2
                predictors[0][4] = predictors[0][0] + (predictors[0][1] - predictors[0][2]) / 2;
                predictors[1][4] = predictors[1][0] + (predictors[1][1] - predictors[1][2]) / 2;
                predictors[2][4] = predictors[2][0] + (predictors[2][1] - predictors[2][2]) / 2;

                // Mode 6 -> b + (a - c) / 2
                predictors[0][5] = predictors[0][1] + (predictors[0][0] - predictors[0][2]) / 2;
                predictors[1][5] = predictors[1][1] + (predictors[1][0] - predictors[1][2]) / 2;
                predictors[2][5] = predictors[2][1] + (predictors[2][0] - predictors[2][2]) / 2;

                // Mode 7 -> (a + b) / 2
                predictors[0][6] = (predictors[0][0] + predictors[0][1]) / 2;
                predictors[1][6] = (predictors[1][0] + predictors[1][1]) / 2;
                predictors[2][6] = (predictors[2][0] + predictors[2][1]) / 2;

                // Select the minimum value
                int min = 300;
                int col = 0;
                for(int i = 0; i < 7; i++){
                    double tot = (predictors[0][i] + predictors[1][i] + predictors[2][i]) / 3;
                    if (tot < min){
                        min = tot;
                        col = i;
                    }
                }

                // Set the minimum value discovered in the specific pixel
                imgPredicted(column,row,0,0) = predictors[0][col];
                imgPredicted(column,row,0,1) = predictors[1][col];
                imgPredicted(column,row,0,2) = predictors[2][col]; 
            }
        }
    }
    return imgPredicted;
}

CImg<unsigned char> ImageCodec::predictionError(){
    CImg<unsigned char> imgYUV420 = ImageCodec::convertToYUV420();
    CImg<unsigned char> imgPredicted = ImageCodec::losslessJPEG(imgYUV420);

    // Get width and height
    int width = imgYUV420.width();
    int height = imgYUV420.height();
 
    // Error image
    CImg<unsigned char> errorImg(width,height,1,3);

    for (int row = 0; row < height; row++){
        for (int column = 0; column < width; column++){
            errorImg(column,row,0,0) = (int) (imgYUV420(column,row,0,0) - imgPredicted(column,row,0,0)); 
        } 
    }
    return errorImg;
}    

void ImageCodec::entropyCoding(string imgName, string fileToWrite){
    Golomb golombEncoder = Golomb(5);
    string code;
    BitStream bs = BitStream(fileToWrite,'w');
    Mat inputFile = imread(imgName);

    // Variable to store the byte from each channel
    int byteFromPixel;

    for(int i = 0; i < inputFile.rows; i++){
        for(int j = 0; j < inputFile.cols; j++){
            for(int channel = 0; channel < inputFile.channels(); channel++){
                byteFromPixel = inputFile.at<Vec3b>(i,j)[channel];
                code = golombEncoder.encodeNumber(byteFromPixel);
                writeSample(bs, code);
            }
        }
    }
}
