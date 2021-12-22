#include "../PartA/Ex1/bitstream.h"
#include "../PartA/Ex3/Golomb.h"
#include "AudioFile/AudioFile.h"
#include <cstdio>
#include <iterator>
#include <ostream>
#include <string>
#include <iostream>
#include <math.h>

class LLAudioCodec
{
    AudioFile<float> sourceAudio;
    AudioFile<float> compressedAudio;
    int m;
    std::string residualFileName;

    public:
    LLAudioCodec(std::string filename, std::string residualFileName, int m)
    {
        this->sourceAudio.load(filename);
        this->m = m;
        this->residualFileName = residualFileName;
    };

    void compressAudio();
    void decompressAudio();
    private:
    void writeSample(BitStream &bs, std::string &code);
    std::string decodeCode(BitStream &bs, short restBits, int &bitsRead);
};

void LLAudioCodec::compressAudio()
{
    Golomb golombEncoder = Golomb(this->m);
    BitStream bs = BitStream(this->residualFileName,'w');
    std::string code;

    // Primeiramente, como os dois primeiros numeros do ficheiro codificado,
    // guardamos o sample rate e o numero de samples por channel, para podermos
    // criar o ficheiro de audio com os mesmos parametros que o ficheiro original
    
    int numSamplePerChannel = this->sourceAudio.getNumSamplesPerChannel();
    code = golombEncoder.encodeNumber(numSamplePerChannel);
    writeSample(bs, code);
    int sourceSampleRate = this->sourceAudio.getSampleRate();
    code = golombEncoder.encodeNumber(sourceSampleRate);
    writeSample(bs, code);

    std::cout << "Samples per channel: " << numSamplePerChannel << std::endl;    
    std::cout << "Sample Rate: " << sourceSampleRate << std::endl;    

    // residuais
    float res0_l,res0_r, prev_res0_r, prev_res0_l;
    float res1_l,res1_r, prev_res1_r, prev_res1_l;
    float res2_l,res2_r, prev_res2_r, prev_res2_l;
    float res3_l,res3_r;

    // todas as samples do canal direito e esquerdo
    std::vector<float> left_channel = sourceAudio.samples[0];
    std::vector<float> right_channel = sourceAudio.samples[1];
    
    // começamos na sample 3, pelo que temos de colocar nestas
    // variaveis auxiliares os valores das 3 primeiras samples

    prev_res0_r = right_channel[0];
    prev_res0_l = left_channel[0];
    prev_res1_r = right_channel[1];
    prev_res1_l = left_channel[1];
    prev_res2_r = right_channel[2];
    prev_res2_l = left_channel[2];

    int integer_left;
    int integer_right;

    for(int nsample=3; nsample<sourceAudio.getNumSamplesPerChannel(); nsample++)
    {
        // Multiplicar por 2^15, pois os valores são floats.
        // Na hora de descodificar os codigos de golomb, temos
        // de recordar que após a conversão, é necessário dividir por 
        // 2^15
        
        // calculo dos residuais direitos
        res0_r = right_channel[nsample];
        res1_r = res0_r - prev_res0_r;
        res2_r = res1_r - prev_res1_r;
        res3_r = res2_r - prev_res2_r;

        prev_res0_r = res0_r;
        prev_res1_r = res1_r;
        prev_res2_r = res2_r;

        // calculo dos residuais esquerdos
        res0_l = left_channel[nsample];
        res1_l = res0_l - prev_res0_l;
        res2_l = res1_l - prev_res1_l;
        res3_l = res2_l - prev_res2_l;
        
        prev_res0_l = res0_l;
        prev_res1_l = res1_l;
        prev_res2_l = res2_l;
        

        // Multiplicar por 2^15 (32768)
        integer_left = res3_l * 32768; 
        code = golombEncoder.encodeNumber(integer_left);
        writeSample(bs, code);

        integer_right = res3_r * 32768; 
        code = golombEncoder.encodeNumber(integer_right);
        writeSample(bs, code);
    }
    bs.close();
}

void LLAudioCodec::decompressAudio()
{
    Golomb golombDecoder = Golomb(this->m);
    BitStream bs = BitStream(this->residualFileName,'r');
    AudioFile<float> outFile;
    outFile.setNumChannels(2);

    int bitsInFile = bs.getByteSize()*8;
    int bitsRead = 0;
    short restBits = ceil(log(golombDecoder.m)/log(2));
    std::string code;

    // valores
    float val0_l, val0_r, prev_val0_r, prev_val0_l;
    float val1_l, val1_r, prev_val1_r, prev_val1_l;
    float val2_l, val2_r, prev_val2_r, prev_val2_l;
    float val3_l, val3_r;
  
    int left_channel_sample,right_channel_sample;
    short headerFlag  = 1;
    short firstSamplesFlag = 1;
    int samplesRead = 3;
    int sampleRate;
    int samplesPerChannel;
    while (bitsRead < (bitsInFile-11)) 
    {
        if(headerFlag)
        {
            code = decodeCode(bs,restBits,bitsRead);
            samplesPerChannel= golombDecoder.decodeNumber(code);
            std::cout << "Samples per channel: " << samplesPerChannel << std::endl;    
            code = decodeCode(bs,restBits,bitsRead);
            sampleRate = golombDecoder.decodeNumber(code);
            std::cout << "Sample Rate: " << sampleRate << std::endl;    
            headerFlag = 0;
            outFile.setNumSamplesPerChannel(samplesPerChannel);
            outFile.setSampleRate(sampleRate);
        }
    
        // LEMBRAR QUE A SAMPLE DO CANAL ESQUERDO É A PRIMEIRA
        if(firstSamplesFlag)
        {
            code = decodeCode(bs, restBits, bitsRead); 
            left_channel_sample = golombDecoder.decodeNumber(code);
            prev_val0_l = (float)(left_channel_sample)/32768;
            outFile.samples[0][0] = prev_val0_l;
            
            code = decodeCode(bs, restBits, bitsRead); 
            right_channel_sample = golombDecoder.decodeNumber(code);
            prev_val0_r = (float)(right_channel_sample)/32768;
            outFile.samples[1][0] = prev_val0_r;

        //////////////////////////////////////////////////////////////
            code = decodeCode(bs, restBits, bitsRead); 
            left_channel_sample = golombDecoder.decodeNumber(code);
            prev_val1_l = (float)(left_channel_sample)/32768;
            outFile.samples[0][1] = prev_val1_l;
            
            code = decodeCode(bs, restBits, bitsRead); 
            right_channel_sample = golombDecoder.decodeNumber(code);
            prev_val1_r = (float)(right_channel_sample)/32768;
            outFile.samples[1][1] = prev_val1_r;

    //////////////////////////////////////////////////////////////////
            code = decodeCode(bs, restBits, bitsRead); 
            left_channel_sample = golombDecoder.decodeNumber(code);
            prev_val2_l = (float)(left_channel_sample)/32768;
            outFile.samples[0][2] = prev_val2_l;
            
            code = decodeCode(bs, restBits, bitsRead); 
            right_channel_sample = golombDecoder.decodeNumber(code);
            prev_val2_r = (float)(right_channel_sample)/32768;
            outFile.samples[1][2] = prev_val2_r;

            firstSamplesFlag=0;
        }

        // O primeiro número é sempre a sample do Left Channel
        code = decodeCode(bs,restBits,bitsRead);
        left_channel_sample = golombDecoder.decodeNumber(code);
        val3_l = float(left_channel_sample)/32768;
        val2_l = val3_l + prev_val2_l;
        prev_val2_l = val2_l;
        val1_l = val2_l + prev_val1_l;
        prev_val1_l = val1_l;
        val0_l = val1_l + prev_val0_l;
        prev_val0_l = val0_l;
    
        // TEM BUG AQUI, FALTA DESCOBRIR O PORQUE DOS RESIDUAIS NAO ESTAREM A SER 
        // CALCULADOS CORRETAMENTE
        // PARA JÁ, FICA COM O VALOR DA SAMPLE SEM CALCULO DO RESIDUAL
        outFile.samples[0][samplesRead] = val3_l;

        // Segundo número é do right channel
        code = decodeCode(bs,restBits,bitsRead);
        right_channel_sample = golombDecoder.decodeNumber(code);
        val3_r = (float)right_channel_sample/32768;
        val2_r = val3_r + prev_val2_r;
        prev_val2_r = val2_r;
        val1_r = val2_r + prev_val1_r;
        prev_val1_r = val1_r;
        val0_r = val1_l + prev_val0_r;
        prev_val0_r = val0_r;

        // TEM BUG AQUI, FALTA DESCOBRIR O PORQUE DOS RESIDUAIS NAO ESTAREM A SER 
        // CALCULADOS CORRETAMENTE
        // PARA JÁ, FICA COM O VALOR DA SAMPLE SEM CALCULO DO RESIDUAL
        outFile.samples[1][samplesRead] = val3_r;

        samplesRead++;
    }
    bs.close();
    std::cout << "Samples Read: " << samplesRead << std::endl;
    outFile.save("outfile",AudioFileFormat::Wave); 
}

void LLAudioCodec::writeSample(BitStream &stream, std::string &code)
{
    for(auto &ch : code)
    {
        if(ch=='0') stream.writeBit(0);
        if(ch=='1') stream.writeBit(1);
    }
}

std::string LLAudioCodec::decodeCode(BitStream &stream, short restBits, int &n)
{
    unsigned char out;
    std::string decode="";
    out = stream.readBit();
    n++;

    while(out!=0x00)
    {
        decode = decode + '1';
        out = stream.readBit();
        n++;
    }

    decode = decode + '0';
    for(int i = 0; i<restBits;i++)
    {
        out = stream.readBit();
        if(out == 0x00) decode = decode + '0';
        if(out == 0x01) decode = decode + '1';
        n++;
    }

    return decode;
}
