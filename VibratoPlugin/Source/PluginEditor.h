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
class VibratoPluginAudioProcessorEditor  : public AudioProcessorEditor,
                                           private Slider::Listener,
                                           private ToggleButton::Listener
{
public:
    VibratoPluginAudioProcessorEditor (VibratoPluginAudioProcessor&);
    ~VibratoPluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    float getDepthSliderValueInS();
    float getModFreqSliderValueInHz();

private:
    void sliderValueChanged (Slider* slider) override;
    void buttonStateChanged (Button* button) override;
    void buttonClicked (Button* button) override;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VibratoPluginAudioProcessor& processor;

    Slider sliderModWidth {Slider::RotaryVerticalDrag, Slider::TextBoxBelow};
    Label labelModWidth;
    Slider sliderModFreq {Slider::RotaryVerticalDrag, Slider::TextBoxBelow};
    Label labelModFreq;
    ToggleButton buttonBypass {"Bypass"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratoPluginAudioProcessorEditor)
};
