#include <string>
#include <iostream>  
#include "./LLAudioCodec.cpp"

int main(int argc, char *argcv[])
{
    LLAudioCodec codec1 = LLAudioCodec("source.wav","outAudio/out.wav", "outResidual/outSource.txt",2048);
    LLAudioCodec codec2 = LLAudioCodec("sample05.wav","outAudio/out05.wav", "outResidual/out05.txt",2048);
    LLAudioCodec codec3 = LLAudioCodec("sample07.wav","outAudio/out07.wav", "outResidual/out07.txt",2048);
    
    codec1.compressAudio();
    codec2.compressAudio();
    codec3.compressAudio();
    
    
    std::cout << "\n-----------------------------------------------------------" << std::endl;


    codec1.decompressAudio();
    codec2.decompressAudio();
    codec3.decompressAudio();
    return 0;
}
