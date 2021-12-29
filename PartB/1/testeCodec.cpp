#include <string>
#include <iostream>  
#include "AudioCodec.h"
#include <chrono>

int main(int argc, char *argcv[])
{
    AudioCodec codec1 = AudioCodec("samples/sample01.wav","outAudio/out01.wav", "outResidual/out01.txt",2048);
    AudioCodec codec2 = AudioCodec("samples/sample02.wav","outAudio/out02.wav", "outResidual/out02.txt",2048);
    AudioCodec codec3 = AudioCodec("samples/sample03.wav","outAudio/out03.wav", "outResidual/out03.txt",2048);
    AudioCodec codec4 = AudioCodec("samples/sample04.wav","outAudio/out04.wav", "outResidual/out04.txt",2048);
    AudioCodec codec5 = AudioCodec("samples/sample05.wav","outAudio/out05.wav", "outResidual/out05.txt",2048);
    AudioCodec codec6 = AudioCodec("samples/sample06.wav","outAudio/out06.wav", "outResidual/out06.txt",2048);
    AudioCodec codec7 = AudioCodec("samples/sample07.wav","outAudio/out07.wav", "outResidual/out07.txt",2048);
    
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    codec1.compressAudioLossless();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for encoding sample01.wav = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;
    
    begin = std::chrono::steady_clock::now();
    codec2.compressAudioLossless();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for encoding sample02.wav = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec3.compressAudioLossless();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for encoding sample03.wav = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec4.compressAudioLossless();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for encoding sample04.wav = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec5.compressAudioLossless();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for encoding sample05.wav = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec6.compressAudioLossless();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for encoding sample06.wav = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec7.compressAudioLossless();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for encoding sample07.wav = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "ms" << std::endl;

    std::cout << "\n------------------------ DECODING -----------------------------------" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec1.decompressAudio();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for decompressing sample01 residuals = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec2.decompressAudio();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for decompressing sample02 residuals = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;
    
    begin = std::chrono::steady_clock::now();
    codec3.decompressAudio();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for decompressing sample03 residuals = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec4.decompressAudio();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for decompressing sample04 residuals = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec5.decompressAudio();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for decompressing sample05 residuals = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec6.decompressAudio();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for decompressing sample06 residuals = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;

    begin = std::chrono::steady_clock::now();
    codec7.decompressAudio();
    end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed for decompressing sample07 residuals = " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << "s" << std::endl;

    return 0;
}
