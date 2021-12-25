#pragma once
#include "./AudioFile/AudioFile.h"
#include "../../PartA/Ex1/bitstream.h"
#include <string>

class AudioCodec
{
   AudioFile<float> sourceAudio;
   AudioFile<float> compressedAudio;
   int m;
   std::string residualFileName;
   std::string outAudio;

   public:
   AudioCodec(std::string sourceAudio, std::string outAudio, std::string residualFileName, int m);
   void compressAudio();
   void decompressAudio();
   void residualsHistogram();

   private:
   void writeSample(BitStream &bs, std::string &code);
   std::string decodeCode(BitStream &bs, short restBits, int &bitsRead);
};

