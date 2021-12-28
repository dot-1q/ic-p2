#include "../../PartA/3/Golomb.h"
#include "../../PartA/1/bitstream.h"
#include "CImg.h"
#include "ImageCodec.h"
#include <string>
#include <cmath>
#include <iostream>
#include <array>

using namespace cimg_library;

ImageCodec::ImageCodec(std::string fileName)
{
        this->image = fileName;
}

CImg<unsigned char> ImageCodec::convertToYUV420()
{
    // Image to transform
    CImg<unsigned char> image(this->image.c_str());

    // Get width and height
    int width = image.width();
    int height = image.height();

    // Image converted to YUV 420 with the same dimensions 
    CImg<unsigned char> imgYUV(width,height,1,3);

    int r,g,b;
    int y,u,v;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // Get the RGB values from the initial image
            r = (int)image(column,row,0,0); 
            g = (int)image(column,row,0,1); 
            b = (int)image(column,row,0,2); 

            // Calculate the YUV values
            y = (int) ((0.2990 * r) + (0.5870 * g) + (0.1140 * b));
            u = (int) ((-0.1684 * r) - (0.3316 * g) + (0.5 * b) + 128);
            v = (int) ((0.5 * r) - (0.4187 * g) - (0.0813 * b) + 128);

            if(column % 2 == 0)
            {
                // (y,u,0)
                if(row % 2 == 0)
                {
                    imgYUV(column,row,0,0) = y;
                    imgYUV(column,row,0,1) = u;
                    imgYUV(column,row,0,2) = 0;
                }
                // (y,0,v)
                else
                {
                    imgYUV(column,row,0,0) = y;
                    imgYUV(column,row,0,1) = 0;
                    imgYUV(column,row,0,2) = v;
                }
            }
            //(y,0,0)
            else
            {
                imgYUV(column,row,0,0) = y;
                imgYUV(column,row,0,1) = 0;
                imgYUV(column,row,0,2) = 0; 
            }
        }
    }
    return imgYUV;
}

void ImageCodec::losslessJPEG(CImg<unsigned char> image, std::string outResFile,int predictMode, int m)
{
    Golomb golombEncoder = Golomb(m);
    BitStream bs = BitStream(outResFile,'w');
    std::string code;

    // The first 3 numbers on the residuals file are
    // the width, height, and predictive mode

    // Get width and height
    int width = image.width();
    code = golombEncoder.encodeNumber(width);
    writeColor(bs,code);
    int height = image.height();
    code = golombEncoder.encodeNumber(height);
    writeColor(bs,code);

    code = golombEncoder.encodeNumber(predictMode);
    writeColor(bs,code);
    
    // array to store the predictors values 
    // accoding the the mode selected
    
    std::array<int, 3> predictors;
    int y,u,v;

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // If it's a border pixel
            if( (row == 0) || (row == height-1) || (column == 0) || (column == width-1) )
            {

                // The data stays the same
                y = image(column,row,0,0);
                code = golombEncoder.encodeNumber(y);
                writeColor(bs,code);
                u = image(column,row,0,1);
                code = golombEncoder.encodeNumber(u);
                writeColor(bs,code);
                v = image(column,row,0,2);
                code = golombEncoder.encodeNumber(v);
                writeColor(bs,code);
            }
            // If it's an inner pixel
            else
            {
                // Depending on the JPEG mode, get the predictive values 
                predictors = getPredictedValues(predictMode, column, row, image); 


                // We store on the residual files, the Original pixel 
                // minus the predictive value
                // ENCODED = ORIGINAL - PREDICTED

                y = image(column,row,0,0) - predictors[0];
                code = golombEncoder.encodeNumber(y);
                writeColor(bs,code);
                u = image(column,row,0,1) - predictors[1]; 
                code = golombEncoder.encodeNumber(u);
                writeColor(bs,code);
                v = image(column,row,0,2) - predictors[2]; 
                code = golombEncoder.encodeNumber(v);
                writeColor(bs,code);
            }
        }
    }
    bs.close();
}

void ImageCodec::lossyJPEG(CImg<unsigned char> image, std::string outResFile,int predictMode, int m, int Ylb, int Ulb, int Vlb)
{
    Golomb golombEncoder = Golomb(m);
    BitStream bs = BitStream(outResFile,'w');
    std::string code;

    // The first 3 numbers on the residuals file are
    // the width, height, and predictive mode

    // Get width and height
    int width = image.width();
    code = golombEncoder.encodeNumber(width);
    writeColor(bs,code);
    int height = image.height();
    code = golombEncoder.encodeNumber(height);
    writeColor(bs,code);

    code = golombEncoder.encodeNumber(predictMode);
    writeColor(bs,code);
    
    // array to store the predictors values 
    // accoding the the mode selected
    
    std::array<int, 3> predictors;
    int y,u,v;

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // If it's a border pixel
            if( (row == 0) || (row == height-1) || (column == 0) || (column == width-1) )
            {
                // The data stays the same
                y = image(column,row,0,0) >> Ylb;
                code = golombEncoder.encodeNumber(y);
                writeColor(bs,code);
                u = image(column,row,0,1) >> Ulb;
                code = golombEncoder.encodeNumber(u);
                writeColor(bs,code);
                v = image(column,row,0,2) >> Vlb;
                code = golombEncoder.encodeNumber(v);
                writeColor(bs,code);
            }
            // If it's an inner pixel
            else
            {
                // Depending on the JPEG mode, get the predictive values 
                predictors = getLossyPredictedValues(predictMode, column, row, image, Ylb, Ulb, Vlb); 


                // We store on the residual files, the Original pixel 
                // minus the predictive value
                // ENCODED = ORIGINAL >> N - PREDICTED >> N
                // Note that the predicted has already been shifted by the
                // selected ammount in their calculation process

                y = (image(column,row,0,0) >> Ylb) - predictors[0];
                code = golombEncoder.encodeNumber(y);
                writeColor(bs,code);
                u = (image(column,row,0,1) >> Ulb) - predictors[1]; 
                code = golombEncoder.encodeNumber(u);
                writeColor(bs,code);
                v = (image(column,row,0,2) >> Vlb) - predictors[2]; 
                code = golombEncoder.encodeNumber(v);
                writeColor(bs,code);
            }
        }
    }
    bs.close();
}

void ImageCodec::decompressImage(std::string residualsFileName, const char* outFilename, int m)
{
    Golomb golombDecoder = Golomb(m);
    BitStream bs = BitStream(residualsFileName,'r');
    std::string code;

    int bitsInFile = bs.getByteSize()*8;
    int bitsRead = 0;
    short restBits = ceil(log(m)/log(2));
    
    // READING HEADER //
    // Width, height and predict Mode were encoded 
    // by that order

    code = decodeCode(bs, restBits, bitsRead);
    int width = golombDecoder.decodeNumber(code);
    code = decodeCode(bs, restBits, bitsRead);
    int height = golombDecoder.decodeNumber(code);
    code = decodeCode(bs, restBits, bitsRead);
    int predictMode = golombDecoder.decodeNumber(code);

    CImg<unsigned char> decompressedImage(width,height,1,3);
    int y,u,v;
    int a,b,c;
    std::array<int,3> predictors;


    // We stored the pixel values from TOP to BOTTOM and LEFT to RIGHT
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            if( (row == 0) || (row == height-1) || (column == 0) || (column == width-1) )
            {
                 
                // Border pixel values were not changed from the original
                code = decodeCode(bs, restBits, bitsRead);
                y = golombDecoder.decodeNumber(code);
                code = decodeCode(bs, restBits, bitsRead);
                u = golombDecoder.decodeNumber(code);
                code = decodeCode(bs, restBits, bitsRead);
                v = golombDecoder.decodeNumber(code);

                decompressedImage(column,row,0,0) = y;
                decompressedImage(column,row,0,1) = u;
                decompressedImage(column,row,0,2) = v;
            }
            else
            {
                // READ THE RESIDUAL VALUE ENCODED ON THE FILE
                code = decodeCode(bs, restBits, bitsRead);
                y = golombDecoder.decodeNumber(code);
                code = decodeCode(bs, restBits, bitsRead);
                u = golombDecoder.decodeNumber(code);
                code = decodeCode(bs, restBits, bitsRead);
                v = golombDecoder.decodeNumber(code);


                // FROM THE PREDICTED MODE, GET THE PREDICTED VALUES ACCORDINGLY
                predictors = getPredictedValues(predictMode, column, row, decompressedImage);

                //  SINCE WE ENCODED   ENCODED = ORIGINAL - PREDICTED
                //  THE DECOMPRESSED SHOULD BE      ORIGINAL = ENCODED + PREDICTED

                decompressedImage(column,row,0,0) = (y + predictors[0]);
                decompressedImage(column,row,0,1) = (u + predictors[1]);
                decompressedImage(column,row,0,2) = (v + predictors[2]);

            }
        }
    }
    bs.close();
    decompressedImage.save(outFilename);
}

void ImageCodec::writeColor(BitStream &stream, std::string &code)
{
    for(auto &ch : code)
    {
        if(ch=='0') stream.writeBit(0);
        if(ch=='1') stream.writeBit(1);
    }
}

std::string ImageCodec::decodeCode(BitStream &stream, short restBits, int &n)
{
    unsigned char out;
    std::string decode="";
    out = stream.readBit();
    n++;

    while(out!=0x00)
    {
        decode = decode + '1';
        out = stream.readBit();
        n++;
    }

    decode = decode + '0';
    for(int i = 0; i<restBits;i++)
    {
        out = stream.readBit();
        if(out == 0x00) decode = decode + '0';
        if(out == 0x01) decode = decode + '1';
        n++;
    }

    return decode;
}

std::array<int,3> ImageCodec::getPredictedValues(int predictMode,int column,int row, CImg<unsigned char> &image)
{
    int predictors[3][7];
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
    
    return std::array<int, 3>() = {predictors[0][predictMode],predictors[1][predictMode],predictors[2][predictMode]};
}

std::array<int,3> ImageCodec::getLossyPredictedValues(int predictMode,int column,int row, CImg<unsigned char> &image, int Ylb, int Ulb, int Vlb)
{
    int predictors[3][7];
    // Mode 1 -> a
    predictors[0][0] = image(column-1,row,0,0) >> Ylb;
    predictors[1][0] = image(column-1,row,0,1) >> Ulb;
    predictors[2][0] = image(column-1,row,0,2) >> Vlb;

    // Mode 2 -> b
    predictors[0][1] = image(column,row-1,0,0) >> Ylb;
    predictors[1][1] = image(column,row-1,0,1) >> Ulb;
    predictors[2][1] = image(column,row-1,0,2) >> Vlb;

    // Mode 3 -> c 
    predictors[0][2] = image(column-1,row-1,0,0) >> Ylb;
    predictors[1][2] = image(column-1,row-1,0,1) >> Ulb;
    predictors[2][2] = image(column-1,row-1,0,2) >> Vlb;

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
    
    return std::array<int, 3>() = {predictors[0][predictMode],predictors[1][predictMode],predictors[2][predictMode]};
}
