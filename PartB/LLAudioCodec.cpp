#include "../PartA/Ex1/bitstream.cpp"
#include "../PartA/Ex3/Golomb.cpp"
#include "AudioFile/AudioFile.h"
#include <string>
#include <iostream>

class LLAudioCodec
{
    AudioFile<double> sourceAudio;
    AudioFile<double> compressedAudio;
    int m;

    public:
    LLAudioCodec(std::string filename, int m)
    {
        this->sourceAudio.load(filename);
        this->m = m;
    };

    void compressAudio();
    void decompressAudio();
    private:
};

void LLAudioCodec::compressAudio()
{
    Golomb golombEncoder = Golomb(this->m);
    std::string left_code;
    std::string right_code;
    // residuais
    int res0_l,res0_r, prev_res0_r, prev_res0_l;
    int res1_l,res1_r, prev_res1_r, prev_res1_l;
    int res2_l,res2_r, prev_res2_r, prev_res2_l;
    int res3_l,res3_r;

    // todas as samples do canal direito e esquerdo
    std::vector<double> left_channel = sourceAudio.samples[0];
    std::vector<double> right_channel = sourceAudio.samples[1];
    int right_sample;
    int left_sample;

    
    // começamos na sample 3, pelo que temos de colocar nestas
    // variaveis auxiliares os valores das 3 primeiras samples

    prev_res0_r = right_channel[0] * 1000;
    prev_res0_l = left_channel[0] * 1000;
    prev_res1_r = right_channel[1] * 1000;
    prev_res1_l = left_channel[1] * 1000;
    prev_res2_r = right_channel[2] * 1000;
    prev_res2_l = left_channel[2] * 1000;

    for(int nsample=3; nsample<sourceAudio.getNumSamplesPerChannel(); nsample++)
    {
        // Multiplicar por 1000, pois os valores são floats.
        // Na hora de descodificar os codigos de golomb, temos
        // de recorar que aposa conversão, é necessário dividir por 
        // 1000

        right_sample = right_channel[nsample]*1000;
        left_sample = left_channel[nsample]*1000;


        // calculo dos residuais direitos
        res0_r = right_sample;
        res1_r = res0_r - prev_res0_r;
        res2_r = res1_r - prev_res1_r;
        res3_r = res2_r - prev_res2_r;

        // calculo dos residuais esquerdos
        res0_l = left_sample;
        res1_l = res0_l - prev_res0_l;
        res2_l = res1_l - prev_res1_l;
        res3_l = res2_l - prev_res2_l;
        
        
        left_code = golombEncoder.encodeNumber(res3_l);
        right_code = golombEncoder.encodeNumber(res3_r);

        cout << "golomb encoded left: " << left_code << endl;
        cout << "golomb encoded right: " << right_code << endl;
    }

}

void LLAudioCodec::decompressAudio()
{
    
}
