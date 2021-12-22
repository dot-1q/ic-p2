#include <string>
#include <iostream>  
#include "./LLAudioCodec.cpp"

int main(int argc, char *argcv[])
{
    //LLAudioCodec codec8 = LLAudioCodec("source.wav", "out/out8.txt",8);
    //LLAudioCodec codec16 = LLAudioCodec("source.wav", "out/out16.txt",16);
    //LLAudioCodec codec32 = LLAudioCodec("source.wav", "out/out32.txt",32);
    //LLAudioCodec codec64 = LLAudioCodec("source.wav", "out/out64.txt",64);
    //LLAudioCodec codec128 = LLAudioCodec("source.wav", "out/out128.txt",128);
    //LLAudioCodec codec256 = LLAudioCodec("source.wav", "out/out256.txt",256);
    //LLAudioCodec codec512 = LLAudioCodec("source.wav", "out/out512.txt",512);
    //LLAudioCodec codec1024 = LLAudioCodec("source.wav", "out/out1024.txt",1024);
    LLAudioCodec codec2048 = LLAudioCodec("source.wav", "out/out2048.txt",2048);
    //LLAudioCodec codec4096 = LLAudioCodec("source.wav", "out/out4096.txt",4096);
    //LLAudioCodec codec8192 = LLAudioCodec("source.wav", "out/out8192.txt",8192);
    //LLAudioCodec codec10000 = LLAudioCodec("source.wav", "out/out10000.txt",10000);
    
    //codec8.compressAudio();
    //codec16.compressAudio();
    //codec32.compressAudio();
    //codec64.compressAudio();
    //codec128.compressAudio();
    //codec256.compressAudio();
    //codec512.compressAudio();
    //codec1024.compressAudio();
    codec2048.compressAudio();
    //codec4096.compressAudio();
    //codec8192.compressAudio();
    //codec10000.compressAudio();
    


    codec2048.decompressAudio();
    return 0;
}
