#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#ifndef DFT_H
#define DFT_H

#define NULL_WAVE ((struct Wave){NULL , 0})
typedef unsigned int uint;
#define PI 3.14159
#define TAU (PI * 2)


struct Wave
{
    float* data;
    uint samplesPerSecond;
    float duration;
};

struct FreqData
{
    uint freq;
    float phase;
    float ampitude;
};

struct FreqData MultiplyByFreq(struct Wave wave, uint freq);

struct Wave SinWaveByFreq(uint freq, uint samplesPerSecond, float duration, float phase);

struct Wave CosWaveByFreq(uint freq, uint samplesPerSecond, float duration, float phase);

void PrintFreqData(struct FreqData freqData);

#endif
