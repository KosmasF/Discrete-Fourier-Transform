#include "dft.h"

struct FreqData MultiplyByFreq(struct Wave wave, uint freq)
{
    struct Wave sinWave = SinWaveByFreq(freq, wave.samplesPerSecond, wave.duration, 0);
    struct Wave cosWave = CosWaveByFreq(freq, wave.samplesPerSecond, wave.duration, 0);

    uint size = wave.samplesPerSecond * wave.duration;

    double* sinWaveMultiplicationOutput = malloc(size * sizeof(double));
    double* cosWaveMultiplicationOutput = malloc(size * sizeof(double));
    for(int i = 0; i < size; i++)
    {
        sinWaveMultiplicationOutput[i] = sinWave.data[i] * wave.data[i];
        cosWaveMultiplicationOutput[i] = cosWave.data[i] * wave.data[i];
    }

    float sinWaveSum = 0;
    float cosWaveSum = 0;
    for(int i = 0; i < size; i++)
    {
        sinWaveSum += sinWaveMultiplicationOutput[i];
        cosWaveSum += cosWaveMultiplicationOutput[i];
    }

    sinWaveSum /= wave.samplesPerSecond;
    cosWaveSum /= wave.samplesPerSecond;

    float phase = atan2f(cosWaveSum, sinWaveSum);

    free(sinWave.data);
    free(cosWave.data);
    free(sinWaveMultiplicationOutput);
    free(cosWaveMultiplicationOutput);

    return (struct FreqData){freq, phase, (fabsf(sinWaveSum) + fabsf(cosWaveSum)) * 2};
}

struct Wave SinWaveByFreq(uint freq, uint samplesPerSecond, float duration, float phase)
{
    uint size = samplesPerSecond * duration;
    double* waveData = malloc(size * sizeof(double));

    const float divider = samplesPerSecond / TAU / freq;

    for(int i = 0; i < size; i++)
    {        
        waveData[i] = sin((i / divider) + (phase));
    }

    return (struct Wave){waveData, samplesPerSecond, duration};
}

struct Wave CosWaveByFreq(uint freq, uint samplesPerSecond, float duration, float phase)
{
    uint size = samplesPerSecond * duration;
    double* waveData = malloc(size * sizeof(double));

    const float divider = samplesPerSecond / TAU / freq;

    for(int i = 0; i < size; i++)
    {        
        waveData[i] = cos((i / divider) + (phase));
    }

    return (struct Wave){waveData, samplesPerSecond, duration};
}

void PrintFreqData(struct FreqData freqData)
{
    printf("Frequecy: %d , Phase: %f , Ampitude: %f \n", freqData.freq, freqData.phase, freqData.ampitude);
}

struct DFT_data DiscreteFourierTranform(struct Wave wave, uint minFreq, uint maxFreq, int increment, bool logProgress)
{
    size_t numberOfChecks = ((maxFreq - minFreq ) / increment) + 1;
    struct FreqData* output = malloc(numberOfChecks * sizeof(struct FreqData));
    if(logProgress)
        printf("DFT started.\n");
    for(int i = minFreq; i < maxFreq; i+=increment)
    {
        int idx = (i - minFreq) / increment;
        output[idx] = MultiplyByFreq(wave, i);
        if(logProgress && i % (1000 * increment) == 0)
            printf("Calculated freq: %d , %d remaining.\n", i, maxFreq - i);
    }
    if(logProgress)
        printf("DFT ended.\n");
    return (struct DFT_data){minFreq, maxFreq, output, increment};
}
