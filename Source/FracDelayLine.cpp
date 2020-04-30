/*
  ==============================================================================

    FracDelayLine.cpp
    Created: 14 Apr 2020 3:07:01pm
    Author:  DL

  ==============================================================================
*/

#include "FracDelayLine.h"

FracDelayLine::FracDelayLine()
{
    idx = 0;
    circularBufferSize = 0;
    circularBuffer = nullptr;
}

FracDelayLine::~FracDelayLine()
{}

void FracDelayLine::clearBuffer()
{
    std::fill_n(circularBuffer, circularBufferSize, 0.0f);
}

void FracDelayLine::setSize(int size)
{
    if (circularBuffer == nullptr)
    {
        delete[] circularBuffer;
    }

    circularBufferSize = size;
    circularBuffer = new float[circularBufferSize];
    clearBuffer();
}
//wraparound
int FracDelayLine::currentIndex(int idx)
{
    return idx % (circularBufferSize);
}

void FracDelayLine::setSample(float sample)
{
    idx = currentIndex(idx);
    circularBuffer[idx] = sample;
    idx++;
}

float FracDelayLine::getLinInterpSample(float sampleIdx)
{
    float currentSample;
    float readPos = float(idx) - sampleIdx;
    int x;
    int y;
    float frac;

    if (readPos >= circularBufferSize)
    {
        readPos -= circularBufferSize;
    }

    if (readPos < 0)
    {
        readPos += circularBufferSize;
    }

    x = float(readPos);
    y = x + 1;

    if (y == circularBufferSize)
    {
        y = 0;
    }

    frac = readPos - x;

    currentSample = frac * circularBuffer[y] + (1.0f - frac) * circularBuffer[x];
    
    return currentSample;
} 