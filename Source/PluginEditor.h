/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class StereoSanctionAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    StereoSanctionAudioProcessorEditor (StereoSanctionAudioProcessor&);
    ~StereoSanctionAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    StereoSanctionAudioProcessor& processor;

    Slider dryWetSlider;
    Slider delayTimeSlider;
    Slider feedbackGainSlider;
    Slider modDepthSlider;
    Slider modFreqSlider;
    Slider modDelayWidthSlider;
    Slider ringModFreqSlider;
    Slider ringModDepthSlider;
    Slider ringWaveSlider;
    Slider fuzzGainSlider;
    Slider fuzzIntensitySlider;
    Slider panShiftSlider;
    Slider sharpnessFreqSlider;
    
    Label dryWetLabel;
    Label delayTimeLabel;
    Label feedbackGainLabel;
    Label modDepthLabel;
    Label modFreqLabel;
    Label modDelayWidthLabel;
    Label ringModFreqLabel;
    Label ringModDepthLabel;
    Label ringWaveLabel;
    Label fuzzGainLabel;
    Label fuzzIntensityLabel;
    Label panShiftLabel;
    Label sharpnessFreqLabel;

    void sliderValueChanged(Slider* slider) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoSanctionAudioProcessorEditor)
};
