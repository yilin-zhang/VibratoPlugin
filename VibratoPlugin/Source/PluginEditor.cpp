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

    addAndMakeVisible (slVibratoWidth);
    addAndMakeVisible (lbVibratoWidth);
    addAndMakeVisible (slVibratoFreq);
    addAndMakeVisible (lbVibratoFreq);
    addAndMakeVisible (btnBypass);

    // TODO: The following range settings should be changed
    slVibratoWidth.setRange(0.0, 127.0, 1.0);
    slVibratoWidth.setValue(0);
    slVibratoWidth.setTextValueSuffix (" ms");
    lbVibratoWidth.setText("Mod Width", dontSendNotification);
    lbVibratoWidth.attachToComponent(&slVibratoWidth, false);

    slVibratoFreq.setRange(0.0, 127.0, 1.0);
    slVibratoFreq.setValue(0);
    slVibratoFreq.setTextValueSuffix (" Hz");
    lbVibratoFreq.setText("Frequency", dontSendNotification);
    lbVibratoFreq.attachToComponent(&slVibratoFreq, false);

    slVibratoWidth.addListener(this);
    slVibratoFreq.addListener(this);
    btnBypass.addListener(this);
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
    slVibratoWidth.setBounds(50, 80, 100, 100);
    slVibratoFreq.setBounds(200, 80, 100, 100);
    btnBypass.setBounds(10, 10, 100, 50);
}

void VibratoPluginAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (!processor.isBypassed()) {
        if (slider == &slVibratoWidth)
            processor.setDepth(static_cast<float>(slider->getValue()));
        else if (slider == &slVibratoFreq)
            processor.setModulationFrequency(static_cast<float>(slider->getValue()));
    }
}

void VibratoPluginAudioProcessorEditor::buttonStateChanged(Button *button)
{
    std::cout << "state changed" << std::endl;
    std::cout << button->getToggleState() << std::endl;
}

void VibratoPluginAudioProcessorEditor::buttonClicked(Button *button)
{
    std::cout << "button clicked" << std::endl;
    processor.toggleBypass();

}
