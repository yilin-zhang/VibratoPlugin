/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibratoPluginAudioProcessorEditor::VibratoPluginAudioProcessorEditor (VibratoPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible (sliderModWidth);
    //addAndMakeVisible (labelModWidth);
    addAndMakeVisible (sliderModFreq);
    //addAndMakeVisible (labelModFreq);
    addAndMakeVisible (buttonBypass);

    // TODO: The following range settings should be changed
    sliderModWidth.setRange(0.0, 100.0, 0.1);
    sliderModWidth.setValue(0);
    sliderModWidth.setTextValueSuffix (" ms");
    labelModWidth.setText("Mod Width", dontSendNotification);
    labelModWidth.attachToComponent(&sliderModWidth, false);
    labelModWidth.setJustificationType(Justification::centred);

    sliderModFreq.setRange(0.0, 5.0, 0.001);
    sliderModFreq.setValue(0);
    sliderModFreq.setTextValueSuffix (" Hz");
    labelModFreq.setText("Mod Frequency", dontSendNotification);
    labelModFreq.attachToComponent(&sliderModFreq, false);
    labelModFreq.setJustificationType(Justification::centred);

    sliderModWidth.addListener(this);
    sliderModFreq.addListener(this);
    buttonBypass.addListener(this);

    processor.setDepth(getDepthSliderValueInS());
    processor.setModulationFrequency(getModFreqSliderValueInHz());
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

void VibratoPluginAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &sliderModWidth)
        processor.setDepth(getDepthSliderValueInS());
    else if (slider == &sliderModFreq)
        processor.setModulationFrequency(getModFreqSliderValueInHz());
}

void VibratoPluginAudioProcessorEditor::buttonStateChanged(Button *button)
{
}

void VibratoPluginAudioProcessorEditor::buttonClicked(Button *button)
{
    processor.toggleBypass();
}

float VibratoPluginAudioProcessorEditor::getDepthSliderValueInS() {
    return static_cast<float>(sliderModWidth.getValue()/1000);
}

float VibratoPluginAudioProcessorEditor::getModFreqSliderValueInHz() {
    return static_cast<float>(sliderModFreq.getValue());
}