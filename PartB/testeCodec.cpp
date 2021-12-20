#include <string>
#include <iostream>  
#include "./LLAudioCodec.cpp"

int main(int argc, char *argcv[])
{
    LLAudioCodec codec = LLAudioCodec("source.wav", 5);
    
    codec.compressAudio();

    return 0;
}
