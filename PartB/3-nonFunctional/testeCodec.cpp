#include <string>
#include <iostream>  
#include "../1/AudioCodec.h"

int main(int argc, char *argcv[])
{
    AudioCodec codec1 = AudioCodec("source.wav","outAudio/out.wav", "outResidual/outSource.txt",2048);
    //AudioCodec codec2 = AudioCodec("sample05.wav","outAudio/out05.wav", "outResidual/out05.txt",2048);
    //AudioCodec codec3 = AudioCodec("sample07.wav","outAudio/out07.wav", "outResidual/out07.txt",2048);
    
    codec1.compressAudioLossy(0.3f);
    //codec2.compressAudioLossy(0.3);
    //codec3.compressAudioLossy(0.3);
    
    
    std::cout << "\n-----------------------------------------------------------" << std::endl;


    codec1.decompressAudio();
    //codec2.decompressAudioLossy(0.3);
    //codec3.decompressAudioLossy(0.3);
    return 0;
}
