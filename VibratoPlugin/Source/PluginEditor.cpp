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

    addAndMakeVisible (slVibratoDepth);
    addAndMakeVisible (lbVibratoDepth);
    addAndMakeVisible (slVibratoFreq);
    addAndMakeVisible (lbVibratoFreq);
    addAndMakeVisible (btnBypass);

    // TODO: The following range settings should be changed
    slVibratoDepth.setRange(0.0, 100.0, 0.1);
    slVibratoDepth.setValue(0);
    slVibratoDepth.setTextValueSuffix (" ms");
    lbVibratoDepth.setText("Depth", dontSendNotification);
    lbVibratoDepth.attachToComponent(&slVibratoDepth, false);
    lbVibratoDepth.setJustificationType(Justification::centred);

    slVibratoFreq.setRange(0.0, 5.0, 0.001);
    slVibratoFreq.setValue(0);
    slVibratoFreq.setTextValueSuffix (" Hz");
    lbVibratoFreq.setText("Mod Frequency", dontSendNotification);
    lbVibratoFreq.attachToComponent(&slVibratoFreq, false);
    lbVibratoFreq.setJustificationType(Justification::centred);

    slVibratoDepth.addListener(this);
    slVibratoFreq.addListener(this);
    btnBypass.addListener(this);

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
    slVibratoDepth.setBounds(50, 80, 100, 100);
    slVibratoFreq.setBounds(200, 80, 100, 100);
    btnBypass.setBounds(10, 10, 100, 50);
}

void VibratoPluginAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &slVibratoDepth)
        processor.setDepth(getDepthSliderValueInS());
    else if (slider == &slVibratoFreq)
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
    return static_cast<float>(slVibratoDepth.getValue()/1000);
}

float VibratoPluginAudioProcessorEditor::getModFreqSliderValueInHz() {
    return static_cast<float>(slVibratoFreq.getValue());
}