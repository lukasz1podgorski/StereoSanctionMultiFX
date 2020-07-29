/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "FracDelayLine.h"

//==============================================================================
/**
*/
class StereoSanctionAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    StereoSanctionAudioProcessor();
    ~StereoSanctionAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float sineLFO(float sampleNum);
    float ringWave(float sampleNum);
    float fuzz(float signal);
    float ringModulator(float sampleNum, float signal);
    
    float time;
    float dTime;

    float dryWetStep;
    float delayTimeStep;
    float feedbackGainStep;
    float modDepthStep;
    float modFreqStep;
    float modDelayWidthStep;
    float ringModIntensityStep;
    float ringModFreqStep;
    float ringWaveStep;
    float fuzzGainStep;
    float fuzzIntensityStep;
    float panShiftStep;
    float sharpnessFreqStep;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoSanctionAudioProcessor)

    FracDelayLine leftCircBuff;
    FracDelayLine rightCircBuff;
    float delayTimeL;
    float delayTimeR;
    dsp::IIR::Filter<float> leftLPF, rightLPF, leftPostLPF, rightPostLPF, ringLPF, fuzzOver, fuzzUnder, fuzzLPF1, fuzzLPF2;
    LinearSmoothedValue<float> smoothedRingModFreq, smoothedModDelayTime, smoothedModDelayWidth, smoothedModFreq,
        smoothedModDepth, smoothedRingIntensity, smoothedFuzzGain, smoothedPanShift;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> LPF;
};
