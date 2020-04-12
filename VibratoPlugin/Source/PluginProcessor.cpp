/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VibratoPluginAudioProcessor::VibratoPluginAudioProcessor() :
#ifndef JucePlugin_PreferredChannelConfigurations
     AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                    ),
#endif
     vibrato(nullptr),
     m_fMaxModWidthInS(0.1),  // TODO: This needs to be set properly
     m_fParamFreqInHz(0.0f),  // TODO: This needs to be set properly
     m_fParamWidthInMs(0.0f),  // TODO: This needs to be set properly
     m_fParamBypassed(0.0f),  // TODO: This needs to be set properly
     parameters(*this, nullptr, Identifier("VibratoPlugin"),
                {
                    std::make_unique<AudioParameterFloat>("freqInHz", "Frequency", 0.0f, 14.0f, 0.0f), // 0~14Hz
                    std::make_unique<AudioParameterFloat>("widthInMs", "Width", 0.0f, 100.0f, 0.0f),   // 0~100ms
                    std::make_unique<AudioParameterBool>("bypassed", "Bypassed", false)
                })
{
    CVibrato::createInstance(vibrato);
    //m_fParamFreqInHz = parameters.getRawParameterValue ("freqInHz");
    //m_fParamWidthInMs = parameters.getRawParameterValue ("widthInMs");
    //m_fParamBypassed = parameters.getRawParameterValue ("bypassed"); // 0.0f or 1.0f

    parameters.addParameterListener("freqInHz", this);
    parameters.addParameterListener("widthInMs", this);
    parameters.addParameterListener("bypassed", this);
}

VibratoPluginAudioProcessor::~VibratoPluginAudioProcessor()
{
    CVibrato::destroyInstance(vibrato);
}

//==============================================================================
const String VibratoPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VibratoPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VibratoPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VibratoPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VibratoPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VibratoPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VibratoPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VibratoPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String VibratoPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void VibratoPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void VibratoPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    vibrato->initInstance(m_fMaxModWidthInS, static_cast<float>(sampleRate), getTotalNumInputChannels());
}

void VibratoPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VibratoPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void VibratoPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    vibrato->process(const_cast<float **>(buffer.getArrayOfReadPointers()), buffer.getArrayOfWritePointers(), buffer.getNumSamples());
}

//==============================================================================
bool VibratoPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VibratoPluginAudioProcessor::createEditor()
{
    return new VibratoPluginAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void VibratoPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void VibratoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    std::unique_ptr<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (parameters.state.getType()))
            parameters.replaceState (ValueTree::fromXml (*xmlState));
}

//==============================================================================
void VibratoPluginAudioProcessor::parameterChanged (const String &parameterID, float newValue)
{
    float modWidthInS;
    float modFreqInHz;
    int bypassed;
    if (parameterID == "widthInMs" || parameterID == "bypassed")
    {
        if (parameterID == "widthInMs")
            m_fParamWidthInMs = newValue;
        else
            m_fParamBypassed = newValue;

        bypassed = round(m_fParamBypassed);
        modWidthInS = m_fParamWidthInMs / 1000;
        vibrato->setParam(CVibrato::kParamModWidthInS, modWidthInS * static_cast<float>(1-bypassed));
    }
    else if (parameterID == "freqInHz")
    {
        m_fParamFreqInHz = newValue;
        modFreqInHz = m_fParamFreqInHz;
        vibrato->setParam(CVibrato::kParamModFreqInHz, modFreqInHz);
    }
}
//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VibratoPluginAudioProcessor();
}
