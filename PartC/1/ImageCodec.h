#pragma once
#include <string>
#include <array>
#include "CImg.h"
#include "../../PartA/1/bitstream.h"

class ImageCodec
{
    std::string image;

    public:
        ImageCodec(std::string fileName);
        cimg_library::CImg<unsigned char> convertToYUV420();
        void losslessJPEG(cimg_library::CImg<unsigned char> image, std::string outResFile, int predictMode, int m);
        void lossyJPEG(cimg_library::CImg<unsigned char> image, std::string outResFile, int predictMode, int m, int Ylb, int Ulb, int Vlb);
        void decompressImage(std::string residualsFileName, const char* outFileName, int m); 
    
    private:
        void writeColor(BitStream &stream, std::string &code);
        std::string decodeCode(BitStream &stream, short restBits, int &bitsRead);
        std::array<int,3> getPredictedValues(int predictMode, int column, int row, cimg_library::CImg<unsigned char> &image);
        std::array<int,3> getLossyPredictedValues(int predictMode, int column, int row, cimg_library::CImg<unsigned char> &image, int Ylb, int Ulb, int Vlb);
};
