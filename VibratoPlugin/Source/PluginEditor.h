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
class VibratoPluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    VibratoPluginAudioProcessorEditor (VibratoPluginAudioProcessor&, AudioProcessorValueTreeState&);
    ~VibratoPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    float getWidthSliderValueInS();
    float getFreqSliderValueInHz();

private:

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VibratoPluginAudioProcessor& processor;

    Slider sliderModWidth;
    Label labelModWidth;
    Slider sliderModFreq;
    Label labelModFreq;
    ToggleButton buttonBypass;

    AudioProcessorValueTreeState& valueTreeState;

    std::unique_ptr<SliderAttachment> widthAttachment;
    std::unique_ptr<SliderAttachment> freqAttachment;
    std::unique_ptr<ButtonAttachment> bypassAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratoPluginAudioProcessorEditor)
};
