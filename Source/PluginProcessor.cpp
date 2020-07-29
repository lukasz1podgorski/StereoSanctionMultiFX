/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <stdlib.h>
#include <math.h>

//==============================================================================
StereoSanctionAudioProcessor::StereoSanctionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

StereoSanctionAudioProcessor::~StereoSanctionAudioProcessor()
{
}

//==============================================================================
const String StereoSanctionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StereoSanctionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoSanctionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StereoSanctionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StereoSanctionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoSanctionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StereoSanctionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoSanctionAudioProcessor::setCurrentProgram (int index)
{
}

const String StereoSanctionAudioProcessor::getProgramName (int index)
{
    return {};
}

void StereoSanctionAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StereoSanctionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    leftCircBuff.setSize(int(2 * (sampleRate + samplesPerBlock)));
    rightCircBuff.setSize(int(2 * (sampleRate + samplesPerBlock)));

    leftLPF.reset();
    rightLPF.reset();
    leftPostLPF.reset();
    rightPostLPF.reset();
    ringLPF.reset();
    fuzzOver.reset();
    fuzzUnder.reset();
    fuzzLPF1.reset();
    fuzzLPF2.reset();


    time = 0.0f;
    dTime = 1.0f / sampleRate;

    smoothedRingModFreq.reset(sampleRate, 0.05);
    smoothedRingIntensity.reset(sampleRate, 0.01);
    smoothedModDelayTime.reset(sampleRate, 0.01);
    smoothedModDelayWidth.reset(sampleRate, 0.01);
    smoothedModDepth.reset(sampleRate, 0.01);
    smoothedModFreq.reset(sampleRate, 0.05);
    smoothedFuzzGain.reset(sampleRate, 0.01);
    smoothedPanShift.reset(sampleRate, 0.01);
}

void StereoSanctionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StereoSanctionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

float StereoSanctionAudioProcessor::sineLFO(float sampleNum)
{
    return sin(2.0f * double_Pi * smoothedModFreq.getNextValue() * sampleNum);
}

float StereoSanctionAudioProcessor::ringWave(float sampleNum) 
{
    float waveGain = 0.5;
    float waveDelta = 0.15;
    float twoPi = 2.0f * double_Pi;

    switch (int(ringWaveStep))
    {
    case 1:
    {
        //// Sine Wave
        if (smoothedRingModFreq.getNextValue() <= 10.0f) //tremolo mode
        {
            return waveGain * ringLPF.processSample((sin(twoPi * smoothedRingModFreq.getNextValue() * sampleNum) + 1.0f) / 2.0f);

            break;
        }
        else
        {
            return waveGain * ringLPF.processSample(sin(twoPi * smoothedRingModFreq.getNextValue() * sampleNum));

            break;
        }
    }
    case 2:
    {
        //Saw Wave
        float sawWave = ((1.0f + (1.0f - (2.0f * acos((1.0f - waveDelta) * sin(twoPi * (2.0f * smoothedRingModFreq.getNextValue() * sampleNum - 1.0f)))
            / double_Pi)) * (2.0f * atan(sin(twoPi * smoothedRingModFreq.getNextValue() * sampleNum / 2.0f) / waveDelta) / double_Pi)) / 2.0f);

        return waveGain * ringLPF.processSample(sawWave);

        break;
    }
    case 3:
    {
        if (smoothedRingModFreq.getNextValue() == 0.0) //in case Freq = 0, Intensity = 1;
        {
            return waveGain;
            break;
        }
        else
        {
            float triangleWave = 1.0f - (2.0f * acos((1.0f - waveDelta) * sin(twoPi * smoothedRingModFreq.getNextValue() * sampleNum)) / double_Pi);

            return waveGain * ringLPF.processSample(triangleWave);

            break;
        }
    }
    case 4:
    {
        //Square Wave
        if (smoothedRingModFreq.getNextValue() == 0.0) //in case Freq = 0, Intensity = 1;
        {
            return waveGain;
            break;
        }
        else
        {
            waveDelta = 0.2;
            float sqWave = 2.0f / double_Pi * atan(sin(twoPi * smoothedRingModFreq.getNextValue() * sampleNum) / waveDelta);
            return waveGain * ringLPF.processSample(sqWave);
            break;
        }
    }
    }
}

float StereoSanctionAudioProcessor::ringModulator(float sampleNum, float signal)
{
    float ringingSignal = (1.0f - (smoothedRingIntensity.getNextValue() / 100.f)) * signal 
        + smoothedRingIntensity.getNextValue() / 100.f * signal * ringWave(sampleNum);

    return ringingSignal;
}

float StereoSanctionAudioProcessor::fuzz(float signal)
{
    float wetSignal;

    float sigOver = fuzzOver.processSample(signal);
    float siglpf1 = fuzzLPF1.processSample(signal);

    if (siglpf1 > 0)
    {
        wetSignal = 1.0f - exp(smoothedFuzzGain.getNextValue() * (-siglpf1));
    }
    else
    {
        wetSignal = -1.0f + exp(smoothedFuzzGain.getNextValue() * siglpf1);
    }

    float siglpf2 = fuzzLPF2.processSample(wetSignal);
    float sigunder = fuzzUnder.processSample(siglpf2);

    float fuzzSignal = (1.0f - (fuzzIntensityStep / 100.0f)) * signal + fuzzIntensityStep / 100.f * sigunder;

    if (smoothedFuzzGain.getNextValue() == 0.0f && fuzzIntensityStep == 100.0f)
    {
        return signal;
    }
    else
    {
        return fuzzSignal;
    }

    //if (signal > 0)
    //{
    //    wetSignal = 1.0f - exp(smoothedFuzzGain.getNextValue() * (-signal));
    //}
    //else
    //{
    //    wetSignal = -1.0f + exp(smoothedFuzzGain.getNextValue() * signal);
    //}

    //float fuzzSignal = (1.0f - (fuzzIntensityStep / 100.0f)) * signal + fuzzIntensityStep / 100.f * wetSignal;

    //if (smoothedFuzzGain.getNextValue() == 0.0f && fuzzIntensityStep == 100.0f)
    //{
    //    return signal;
    //}
    //else
    //{
    //    return fuzzSignal;
    //}
}

void StereoSanctionAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto sampleNumber = buffer.getNumSamples();

    //input 2khz, 12db rolloff
    //post delay 2.5khz, 30db rolloff
    leftLPF.coefficients = dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(getSampleRate(), 2000.0f);
    rightLPF.coefficients = dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(getSampleRate(), 2000.0f);
    leftPostLPF.coefficients = dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(getSampleRate(), 2500.0f);
    rightPostLPF.coefficients = dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(getSampleRate(), 2500.0f);
    ringLPF.coefficients = dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), sharpnessFreqStep, 0.7f);
    
    fuzzOver.coefficients = dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate()*2.0, 4000.0f, 0.7f);
    fuzzUnder.coefficients = dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate(), 4000.0f, 0.7f);
    fuzzLPF1.coefficients = dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate()*2.0, 4000.0f, 0.7f);
    fuzzLPF2.coefficients = dsp::IIR::Coefficients<float>::makeLowPass(getSampleRate()*2.0, 4000.0f, 0.7f);
    //fuzzOver.coefficients = dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(getSampleRate() * 2.0, 4000.0f);
    //fuzzUnder.coefficients = dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(getSampleRate(), 4000.0f);
    //fuzzLPF1.coefficients = dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(getSampleRate() * 2.0, 4000.0f);
    //fuzzLPF2.coefficients = dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(getSampleRate(), 4000.0f);



    //LPF.state->coefficients = dsp::IIR::Coefficients<float>::makeFirstOrderLowPass(getSampleRate(), 2000.0f);
    
    smoothedRingModFreq.setValue(ringModFreqStep);
    smoothedRingIntensity.setValue(ringModIntensityStep);
    smoothedModDelayTime.setValue(delayTimeStep);
    smoothedModDelayWidth.setValue(modDelayWidthStep);
    smoothedModDepth.setValue(modDepthStep);
    smoothedModFreq.setValue(modFreqStep);
    smoothedFuzzGain.setValue(fuzzGainStep);
    smoothedPanShift.setValue(panShiftStep);

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    auto* leftChannelData = buffer.getWritePointer(0);
    auto* rightChannelData = buffer.getWritePointer(1);
        
        for (int smp = 0; smp < sampleNumber; ++smp)
        {
            //calculate delayTime for each channel
            //prevent audio bugs if 2*Delay <= Width & modFreq > 0.5
            if (2.0f * smoothedModDelayTime.getNextValue() <= smoothedModDelayWidth.getNextValue())
            {
                delayTimeL = getSampleRate() * (smoothedModDelayTime.getNextValue() + smoothedModDelayTime.getNextValue() *
                    smoothedModDepth.getNextValue() * (0.5f * sineLFO(time))) / 1000.0f;

                delayTimeR = getSampleRate() * (smoothedModDelayTime.getNextValue() + smoothedPanShift.getNextValue() +
                    smoothedModDelayTime.getNextValue() * smoothedModDepth.getNextValue() * (0.5f * sineLFO(time))) / 1000.0f;
            }
            else
            {
                delayTimeL = getSampleRate() * (smoothedModDelayTime.getNextValue() + smoothedModDelayWidth.getNextValue() *
                    smoothedModDepth.getNextValue() * (0.5f * sineLFO(time))) / 1000.0f;
                delayTimeR = getSampleRate() * (smoothedModDelayTime.getNextValue() + smoothedPanShift.getNextValue() +
                    smoothedModDelayWidth.getNextValue() * smoothedModDepth.getNextValue() * (0.5f * sineLFO(time))) / 1000.0f;
            }

            //get dry signal sample
            float dryLeft = buffer.getReadPointer(0)[smp];
            float dryRight = buffer.getReadPointer(1)[smp];

            //get sample from Circular Buffer with Fractional Delay based on delayTime and apply post-Delay LPF
            float wetLeft = leftPostLPF.processSample(leftCircBuff.getLinInterpSample(delayTimeL));
            float wetRight = rightPostLPF.processSample(rightCircBuff.getLinInterpSample(delayTimeR));

            //create feedback and apply input LPF
            float leftChannel = leftLPF.processSample(dryLeft + wetLeft * feedbackGainStep);
            float rightChannel = rightLPF.processSample(dryRight + wetRight * feedbackGainStep);
            
            //write to Circular Buffer with Fractional Delay
            leftCircBuff.setSample(leftChannel);
            rightCircBuff.setSample(rightChannel);
                       
            //apply Fuzz
            float leftFuzz = fuzz(wetLeft);
            float rightFuzz = fuzz(wetRight);

            //apply Ring Modulation
            float leftRinging = ringModulator(time, leftFuzz);
            float rightRinging = ringModulator(time, rightFuzz);

            //write to both channels
            leftChannelData[smp] = (1.0f - (dryWetStep / 100.0f)) * dryLeft + (dryWetStep / 100.0f) * leftRinging;
            rightChannelData[smp] = (1.0f - (dryWetStep / 100.0f)) * dryRight + (dryWetStep / 100.0f) * rightRinging;

            time += dTime;

            if (time >= 1.0) {
                time = 0.0;
            }
        }
}

//==============================================================================
bool StereoSanctionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StereoSanctionAudioProcessor::createEditor()
{
    return new StereoSanctionAudioProcessorEditor (*this);
}

//==============================================================================
void StereoSanctionAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void StereoSanctionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoSanctionAudioProcessor();
}
