/*
  ==============================================================================

    FracDelayLine.h
    Created: 14 Apr 2020 3:07:27pm
    Author:  DL

  ==============================================================================
*/

#pragma once

#ifndef FRACDELAYLINE_H_INCLUDED
#define FRACDELAYLINE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <iostream>

class FracDelayLine
{
public:
    FracDelayLine();
    ~FracDelayLine();

    void clearBuffer();
    void setSize(int size);
    int currentIndex(int idx);
    void setSample(float sample);
    float getLinInterpSample(float sampleIdx);

private:
    int idx;
    int circularBufferSize;
    float* circularBuffer;
};

#endif 