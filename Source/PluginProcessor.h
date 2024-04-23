/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SchroederReverb.h"

//==============================================================================
/**
*/
class AlgorithmicReverbAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    AlgorithmicReverbAudioProcessor();
    ~AlgorithmicReverbAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState apvts;
    
    static const juce::StringRef s_DryWet;
    static const juce::StringRef s_ReverbTime;
    static const juce::StringRef s_Diffusion;
    static const juce::StringRef s_LPF;
    
    void tempChanged(float value, int channel);
    
    
private:
    
  //  juce::SharedResourcePointer<SharedImages>     m_pSharedImagesPtr;
    
    int dryWet = 50;
    
    SchroederReverb schroederReverb;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    
    int ParameterVersionHint = 1;
    
    float smoothedReverbTime[2] = {0.f};
    
    float smoothedDiffusion[2] = {0.f};
    
    float smoothedDryWet[2] = {0.f};
    
    float smoothedLPF[2] = {0.f};
    
    float alpha = 0.999f;
    
    float responseTime = 0.05f;
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlgorithmicReverbAudioProcessor)
};
