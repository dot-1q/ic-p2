#pragma once
#include "./AudioFile/AudioFile.h"
#include "../../PartA/1/bitstream.h"
#include <string>
#include <vector>

class AudioCodec
{
   AudioFile<float> sourceAudio;
   AudioFile<float> compressedAudio;
   int m;
   std::string residualFileName;
   std::string outAudio;

   public:
   AudioCodec(std::string sourceAudio, std::string outAudio, std::string residualFileName, int m);
   void compressAudioLossless();
   void compressAudioLossy(int lb);
   void decompressAudio();
   void residualsHistogram();

   private:
   void writeSample(BitStream &bs, std::string &code);
   std::string decodeCode(BitStream &bs, short restBits, int &bitsRead);
};

