#include "../1/AudioCodec.h"

int main(void)
{
    AudioCodec codec = AudioCodec("source.wav", "out.wav", "outResidual.txt",2048l);

    codec.residualsHistogram();
}
