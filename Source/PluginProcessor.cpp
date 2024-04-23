/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

const juce::StringRef AlgorithmicReverbAudioProcessor::s_DryWet = "Dry/Wet";
const juce::StringRef AlgorithmicReverbAudioProcessor::s_ReverbTime = "Reverb Time";
const juce::StringRef AlgorithmicReverbAudioProcessor::s_Diffusion = "Diffusion";
const juce::StringRef AlgorithmicReverbAudioProcessor::s_LPF = "LPF";

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
                       ),
#endif
apvts(*this, nullptr, "Params", createParams())
{
}

AlgorithmicReverbAudioProcessor::~AlgorithmicReverbAudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout AlgorithmicReverbAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_DryWet, ParameterVersionHint}, "Dry/Wet", 0.f, 100.f, 100.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_ReverbTime, ParameterVersionHint}, "Reverb Time", 0.f, 10.f, 0.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_Diffusion, ParameterVersionHint}, "Diffusion", 0.f, 100.f, 100.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{s_LPF, ParameterVersionHint}, "LPF", 20.f, 20000.f, 20000.f));
    
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
    
    alpha = std::exp(-std::log(9.f) / (sampleRate * responseTime) );
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

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    auto numSamples = buffer.getNumSamples();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        smoothedReverbTime[channel] = alpha * smoothedReverbTime[channel] + (1.f - alpha) * schroederReverb.FBGain;
        
        schroederReverb.setFBGain(smoothedReverbTime[channel]);
        
        smoothedDiffusion[channel] = alpha * smoothedDiffusion[channel] + (1.f - alpha) * schroederReverb.APGain;
        
        schroederReverb.setAPGain(smoothedDiffusion[channel]);
        
        smoothedDryWet[channel] = alpha * smoothedDryWet[channel] + (1.f - alpha) * schroederReverb.APGain;
        
        schroederReverb.setAPGain(smoothedDiffusion[channel]);
        
        for( int i=0; i< totalNumInputChannels; ++i) {
            
            float x = buffer[i];
            
            float y = schroederReverb.processSample(x, channel);
            
        }
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
