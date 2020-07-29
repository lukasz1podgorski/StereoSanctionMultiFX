/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StereoSanctionAudioProcessorEditor::StereoSanctionAudioProcessorEditor (StereoSanctionAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize(750, 300);

    dryWetSlider.setSliderStyle(Slider::LinearVertical);
    dryWetSlider.setRange(0.0, 100.0, 1.0);
    dryWetSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    dryWetSlider.setPopupDisplayEnabled(true, true, this);
    dryWetSlider.setTextValueSuffix(" %");
    dryWetSlider.setValue(50.0); addAndMakeVisible(&dryWetSlider);
    dryWetSlider.setColour(Slider::backgroundColourId, Colours::ghostwhite);
    dryWetSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    dryWetSlider.setColour(Slider::trackColourId, Colours::lightseagreen);
    dryWetLabel.attachToComponent(&dryWetSlider, false);
    dryWetLabel.setText("Level", dontSendNotification);
    dryWetLabel.setColour(Label::textColourId, Colours::lightseagreen);
    dryWetLabel.setJustificationType(Justification::centredTop);
    dryWetSlider.addListener(this);

    /*
    LPFCutoffSlider.setSliderStyle(Slider::LinearVertical);
    LPFCutoffSlider.setRange(50.0, 20000.0, 1.0);
    LPFCutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    LPFCutoffSlider.setPopupDisplayEnabled(true, false, this);
    LPFCutoffSlider.setTextValueSuffix(" Hz");
    LPFCutoffSlider.setValue(2000.0); addAndMakeVisible(&LPFCutoffSlider);
    LPFCutoffSlider.setColour(Slider::backgroundColourId, Colours::ghostwhite);
    LPFCutoffSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    LPFCutoffSlider.setColour(Slider::trackColourId, Colours::lightseagreen);
    LPFCutoffLabel.attachToComponent(&LPFCutoffSlider, false);
    LPFCutoffLabel.setText("LPF", dontSendNotification);
    LPFCutoffLabel.setColour(Label::textColourId, Colours::lightseagreen);
    LPFCutoffLabel.setJustificationType(Justification::centredTop);
    LPFCutoffSlider.addListener(this);

    postLPFCutoffSlider.setSliderStyle(Slider::LinearVertical);
    postLPFCutoffSlider.setRange(50.0, 20000.0, 1.0);
    postLPFCutoffSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    postLPFCutoffSlider.setPopupDisplayEnabled(true, false, this);
    postLPFCutoffSlider.setTextValueSuffix(" Hz");
    postLPFCutoffSlider.setValue(2500.0); addAndMakeVisible(&postLPFCutoffSlider);
    postLPFCutoffSlider.setColour(Slider::backgroundColourId, Colours::ghostwhite);
    postLPFCutoffSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    postLPFCutoffSlider.setColour(Slider::trackColourId, Colours::lightseagreen);
    postLPFCutoffLabel.attachToComponent(&postLPFCutoffSlider, false);
    postLPFCutoffLabel.setText("postLPf", dontSendNotification);
    postLPFCutoffLabel.setColour(Label::textColourId, Colours::lightseagreen);
    postLPFCutoffLabel.setJustificationType(Justification::centredTop);
    postLPFCutoffSlider.addListener(this);
    */

    delayTimeSlider.setSliderStyle(Slider::Rotary);
    delayTimeSlider.setRange(1.0, 250.0, 0.1);
    delayTimeSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    delayTimeSlider.setPopupDisplayEnabled(true, true, this);
    delayTimeSlider.setTextValueSuffix(" ms");
    delayTimeSlider.setValue(15.0); addAndMakeVisible(&delayTimeSlider);
    delayTimeSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    delayTimeSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    delayTimeSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    delayTimeLabel.setText("Time", dontSendNotification);
    delayTimeLabel.attachToComponent(&delayTimeSlider, false);
    delayTimeLabel.setColour(Label::textColourId, Colours::lightseagreen);
    delayTimeLabel.setJustificationType(Justification::centredTop);
    delayTimeSlider.addListener(this);

    feedbackGainSlider.setSliderStyle(Slider::Rotary);
    feedbackGainSlider.setRange(0.0, 1.0, 0.01);
    feedbackGainSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    feedbackGainSlider.setPopupDisplayEnabled(true, true, this);
    feedbackGainSlider.setTextValueSuffix(" Gain");
    feedbackGainSlider.setValue(0.5); addAndMakeVisible(&feedbackGainSlider);
    feedbackGainSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    feedbackGainSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    feedbackGainSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    feedbackGainLabel.setText("Feedback", dontSendNotification);
    feedbackGainLabel.attachToComponent(&feedbackGainSlider, false);
    feedbackGainLabel.setColour(Label::textColourId, Colours::lightseagreen);
    feedbackGainLabel.setJustificationType(Justification::centredTop);
    feedbackGainSlider.addListener(this);

    modDepthSlider.setSliderStyle(Slider::Rotary);
    modDepthSlider.setRange(0.0, 1.0, 0.01);
    modDepthSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    modDepthSlider.setPopupDisplayEnabled(true, true, this);
    modDepthSlider.setTextValueSuffix(" Depth");
    modDepthSlider.setValue(0.5); addAndMakeVisible(&modDepthSlider);
    modDepthSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    modDepthSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    modDepthSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    modDepthLabel.setText("Depth", dontSendNotification);
    modDepthLabel.attachToComponent(&modDepthSlider, false);
    modDepthLabel.setColour(Label::textColourId, Colours::lightseagreen);
    modDepthLabel.setJustificationType(Justification::centredTop);
    modDepthSlider.addListener(this);

    modFreqSlider.setSliderStyle(Slider::Rotary);
    modFreqSlider.setRange(0.0, 5.0, 0.5);
    modFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    modFreqSlider.setPopupDisplayEnabled(true, true, this);
    modFreqSlider.setTextValueSuffix(" Hz");
    modFreqSlider.setValue(1.0); addAndMakeVisible(&modFreqSlider);
    modFreqSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    modFreqSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    modFreqSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    modFreqLabel.setText("Rate", dontSendNotification);
    modFreqLabel.attachToComponent(&modFreqSlider, false);
    modFreqLabel.setColour(Label::textColourId, Colours::lightseagreen);
    modFreqLabel.setJustificationType(Justification::centredTop);
    modFreqSlider.addListener(this);

    modDelayWidthSlider.setSliderStyle(Slider::Rotary);
    modDelayWidthSlider.setRange(0.0, 30.0, 1.0);
    modDelayWidthSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    modDelayWidthSlider.setPopupDisplayEnabled(true, true, this);
    modDelayWidthSlider.setTextValueSuffix(" ms");
    modDelayWidthSlider.setValue(2.0); addAndMakeVisible(&modDelayWidthSlider);
    modDelayWidthSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    modDelayWidthSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    modDelayWidthSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    modDelayWidthLabel.setText("Width", dontSendNotification);
    modDelayWidthLabel.attachToComponent(&modDelayWidthSlider, false);
    modDelayWidthLabel.setColour(Label::textColourId, Colours::lightseagreen);
    modDelayWidthLabel.setJustificationType(Justification::centredTop);
    modDelayWidthSlider.addListener(this);

    ringModFreqSlider.setSliderStyle(Slider::Rotary);
    ringModFreqSlider.setRange(0.0, 5000.0, 1.0);
    ringModFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    ringModFreqSlider.setPopupDisplayEnabled(true, true, this);
    ringModFreqSlider.setTextValueSuffix(" Hz");
    ringModFreqSlider.setValue(200.0); addAndMakeVisible(&ringModFreqSlider);
    ringModFreqSlider.setSkewFactorFromMidPoint(70.0);
    ringModFreqSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    ringModFreqSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    ringModFreqSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    ringModFreqLabel.setText("Ring Frequency", dontSendNotification);
    ringModFreqLabel.attachToComponent(&ringModFreqSlider, false);
    ringModFreqLabel.setColour(Label::textColourId, Colours::lightseagreen);
    ringModFreqLabel.setJustificationType(Justification::centredTop);
    ringModFreqSlider.addListener(this);
    
    ringModDepthSlider.setSliderStyle(Slider::Rotary);
    ringModDepthSlider.setRange(0.0, 100.0, 1.0);
    ringModDepthSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    ringModDepthSlider.setPopupDisplayEnabled(true, true, this);
    ringModDepthSlider.setTextValueSuffix(" %");
    ringModDepthSlider.setValue(50.0); addAndMakeVisible(&ringModDepthSlider);
    ringModDepthSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    ringModDepthSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    ringModDepthSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    ringModDepthLabel.setText("Ring Intensity", dontSendNotification);
    ringModDepthLabel.attachToComponent(&ringModDepthSlider, false);
    ringModDepthLabel.setColour(Label::textColourId, Colours::lightseagreen);
    ringModDepthLabel.setJustificationType(Justification::centredTop);
    ringModDepthSlider.addListener(this);

    ringWaveSlider.setSliderStyle(Slider::Rotary);
    ringWaveSlider.setRange(1.0, 4.0, 1.0);
    ringWaveSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    ringWaveSlider.setPopupDisplayEnabled(true, true, this);
    ringWaveSlider.setTextValueSuffix(" Wave");
    ringWaveSlider.setValue(1.0); addAndMakeVisible(&ringWaveSlider);
    ringWaveSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    ringWaveSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    ringWaveSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    ringWaveLabel.setText("Wave", dontSendNotification);
    ringWaveLabel.attachToComponent(&ringWaveSlider, false);
    ringWaveLabel.setColour(Label::textColourId, Colours::lightseagreen);
    ringWaveLabel.setJustificationType(Justification::centredTop);
    ringWaveSlider.addListener(this);

    fuzzGainSlider.setSliderStyle(Slider::Rotary);
    fuzzGainSlider.setRange(0.0, 10.0, 0.1);
    fuzzGainSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    fuzzGainSlider.setPopupDisplayEnabled(true, true, this);
    fuzzGainSlider.setTextValueSuffix(" Gain");
    fuzzGainSlider.setValue(0.2); addAndMakeVisible(&fuzzGainSlider);
    fuzzGainSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    fuzzGainSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    fuzzGainSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    fuzzGainLabel.setText("Fuzz Gain", dontSendNotification);
    fuzzGainLabel.attachToComponent(&fuzzGainSlider, false);
    fuzzGainLabel.setColour(Label::textColourId, Colours::lightseagreen);
    fuzzGainLabel.setJustificationType(Justification::centredTop);
    fuzzGainSlider.addListener(this);

    fuzzIntensitySlider.setSliderStyle(Slider::Rotary);
    fuzzIntensitySlider.setRange(0.0, 100.0, 1.0);
    fuzzIntensitySlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    fuzzIntensitySlider.setPopupDisplayEnabled(true, true, this);
    fuzzIntensitySlider.setTextValueSuffix(" %");
    fuzzIntensitySlider.setValue(50.0); addAndMakeVisible(&fuzzIntensitySlider);
    fuzzIntensitySlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    fuzzIntensitySlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    fuzzIntensitySlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    fuzzIntensityLabel.setText("Fuzz Intensity", dontSendNotification);
    fuzzIntensityLabel.attachToComponent(&fuzzIntensitySlider, false);
    fuzzIntensityLabel.setColour(Label::textColourId, Colours::lightseagreen);
    fuzzIntensityLabel.setJustificationType(Justification::centredTop);
    fuzzIntensitySlider.addListener(this);

    panShiftSlider.setSliderStyle(Slider::Rotary);
    panShiftSlider.setRange(0.0, 5.0, 0.5);
    panShiftSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    panShiftSlider.setPopupDisplayEnabled(true, true, this);
    panShiftSlider.setTextValueSuffix(" ms");
    panShiftSlider.setValue(0.0); addAndMakeVisible(&panShiftSlider);
    panShiftSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    panShiftSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    panShiftSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    panShiftLabel.setText("Panorama Shift", dontSendNotification);
    panShiftLabel.attachToComponent(&panShiftSlider, false);
    panShiftLabel.setColour(Label::textColourId, Colours::lightseagreen);
    panShiftLabel.setJustificationType(Justification::centredTop);
    panShiftSlider.addListener(this);

    sharpnessFreqSlider.setSliderStyle(Slider::Rotary);
    sharpnessFreqSlider.setRange(1000.0, 20000.0, 1.0);
    sharpnessFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    sharpnessFreqSlider.setPopupDisplayEnabled(true, true, this);
    sharpnessFreqSlider.setTextValueSuffix(" Hz");
    sharpnessFreqSlider.setValue(5000.0); addAndMakeVisible(&sharpnessFreqSlider);
    sharpnessFreqSlider.setColour(Slider::thumbColourId, Colours::lightseagreen);
    sharpnessFreqSlider.setColour(Slider::rotarySliderFillColourId, Colours::lightseagreen);
    sharpnessFreqSlider.setColour(Slider::rotarySliderOutlineColourId, Colours::ghostwhite);
    sharpnessFreqLabel.setText("Ring Sharpness", dontSendNotification);
    sharpnessFreqLabel.attachToComponent(&sharpnessFreqSlider, false);
    sharpnessFreqLabel.setColour(Label::textColourId, Colours::lightseagreen);
    sharpnessFreqLabel.setJustificationType(Justification::centredTop);
    sharpnessFreqSlider.addListener(this);
}

StereoSanctionAudioProcessorEditor::~StereoSanctionAudioProcessorEditor()
{
}

//==============================================================================
void StereoSanctionAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::gainsboro);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText(" ", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void StereoSanctionAudioProcessorEditor::resized()
{
    delayTimeSlider.setBounds(30, 60, 100, 100);
    feedbackGainSlider.setBounds(130, 60, 100, 100);
    modFreqSlider.setBounds(230, 60, 100, 100);
    modDepthSlider.setBounds(330, 60, 100, 100);
    modDelayWidthSlider.setBounds(430, 60, 100, 100);
    panShiftSlider.setBounds(530, 60, 100, 100);

    ringModFreqSlider.setBounds(30, 180, 100, 100);
    ringModDepthSlider.setBounds(130, 180, 100, 100);
    sharpnessFreqSlider.setBounds(230, 180, 100, 100);
    ringWaveSlider.setBounds(330, 180, 100, 100);
    fuzzGainSlider.setBounds(430, 180, 100, 100);
    fuzzIntensitySlider.setBounds(530, 180, 100, 100);

    dryWetSlider.setBounds(660, 60, 50, 215);
}

void StereoSanctionAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    processor.dryWetStep = dryWetSlider.getValue();
    processor.delayTimeStep = delayTimeSlider.getValue();
    processor.feedbackGainStep = feedbackGainSlider.getValue();
    processor.modDepthStep = modDepthSlider.getValue();
    processor.modFreqStep = modFreqSlider.getValue();
    processor.modDelayWidthStep = modDelayWidthSlider.getValue();
    processor.ringModFreqStep = ringModFreqSlider.getValue();
    processor.ringModIntensityStep = ringModDepthSlider.getValue();
    processor.ringWaveStep = ringWaveSlider.getValue();
    processor.fuzzGainStep = fuzzGainSlider.getValue();
    processor.fuzzIntensityStep = fuzzIntensitySlider.getValue();
    processor.panShiftStep = panShiftSlider.getValue();
    processor.sharpnessFreqStep = sharpnessFreqSlider.getValue();
}
