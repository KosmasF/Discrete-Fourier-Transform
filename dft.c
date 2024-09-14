#include "dft.h"

struct FreqData MultiplyByFreq(struct Wave wave, uint freq)
{
    struct Wave sinWave = SinWaveByFreq(freq, wave.samplesPerSecond, wave.duration, 0);
    struct Wave cosWave = CosWaveByFreq(freq, wave.samplesPerSecond, wave.duration, 0);

    uint size = wave.samplesPerSecond * wave.duration;

    float* sinWaveMultiplicationOutput = malloc(size * sizeof(float));
    float* cosWaveMultiplicationOutput = malloc(size * sizeof(float));
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

    return (struct FreqData){freq, phase, (fabsf(sinWaveSum) + fabsf(cosWaveSum)) * 2};
}

struct Wave SinWaveByFreq(uint freq, uint samplesPerSecond, float duration, float phase)
{
    uint size = samplesPerSecond * duration;
    float* waveData = malloc(size * sizeof(float));

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
    float* waveData = malloc(size * sizeof(float));

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
