/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

const juce::StringRef SchroederReverb::temp = "temp";

//==============================================================================
AlgorithmicReverbAudioProcessor::AlgorithmicReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
apvts(*this, nullptr, "Params", createParams())
{
}

AlgorithmicReverbAudioProcessor::~AlgorithmicReverbAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout SchroederReverb::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{temp, ParameterVersionHint}, "Low Threshold", -96.f, 0.f, 0.f));
    
    return {params.begin(), params.end()};
    
}



//==============================================================================
const juce::String AlgorithmicReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AlgorithmicReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AlgorithmicReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AlgorithmicReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AlgorithmicReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AlgorithmicReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AlgorithmicReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AlgorithmicReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AlgorithmicReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void AlgorithmicReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AlgorithmicReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    schroederReverb.prepare(sampleRate);
}

void AlgorithmicReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AlgorithmicReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void AlgorithmicReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
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
    
    auto numSamples = buffer.getNumSamples();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        schroederReverb.process(channelData, numSamples, channel);
    }
}

//==============================================================================
bool AlgorithmicReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AlgorithmicReverbAudioProcessor::createEditor()
{
    return new AlgorithmicReverbAudioProcessorEditor (*this);
}

//==============================================================================
void AlgorithmicReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto currentState = apvts.copyState();
    
    std::unique_ptr<juce::XmlElement> xml (currentState.createXml());
    
    copyXmlToBinary(*xml, destData);
}

void AlgorithmicReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    
    juce::ValueTree newTree = juce::ValueTree::fromXml(*xml);
    
    apvts.replaceState(newTree);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AlgorithmicReverbAudioProcessor();
}
