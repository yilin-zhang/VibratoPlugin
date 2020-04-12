/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibratoPluginAudioProcessorEditor::VibratoPluginAudioProcessorEditor (VibratoPluginAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p),
      processor (p),
      sliderModWidth {Slider::RotaryVerticalDrag, Slider::TextBoxBelow },
      sliderModFreq {Slider::RotaryVerticalDrag, Slider::TextBoxBelow},
      buttonBypass {"Bypass"},
      valueTreeState (vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible (sliderModWidth);
    addAndMakeVisible (sliderModFreq);
    addAndMakeVisible (buttonBypass);

    sliderModWidth.setTextValueSuffix (" ms");
    labelModWidth.setText("Width", dontSendNotification);
    labelModWidth.attachToComponent(&sliderModWidth, false);
    labelModWidth.setJustificationType(Justification::centred);
    widthAttachment.reset(new SliderAttachment (valueTreeState, "widthInMs", sliderModWidth));

    sliderModFreq.setTextValueSuffix (" Hz");
    labelModFreq.setText("Frequency", dontSendNotification);
    labelModFreq.attachToComponent(&sliderModFreq, false);
    labelModFreq.setJustificationType(Justification::centred);
    freqAttachment.reset(new SliderAttachment (valueTreeState, "freqInHz", sliderModFreq));

    bypassAttachment.reset(new ButtonAttachment (valueTreeState, "bypassed", buttonBypass));
}

VibratoPluginAudioProcessorEditor::~VibratoPluginAudioProcessorEditor()
{
}

//==============================================================================
void VibratoPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    //g.setColour (Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void VibratoPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    sliderModWidth.setBounds(50, 80, 100, 100);
    sliderModFreq.setBounds(200, 80, 100, 100);
    buttonBypass.setBounds(10, 10, 100, 50);
}
