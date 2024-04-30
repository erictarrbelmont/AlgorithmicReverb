/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AlgorithmicReverbAudioProcessorEditor::AlgorithmicReverbAudioProcessorEditor (AlgorithmicReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), mainComponent(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 700);
    
    addAndMakeVisible(mainComponent);
}

AlgorithmicReverbAudioProcessorEditor::~AlgorithmicReverbAudioProcessorEditor()
{
}

//==============================================================================
void AlgorithmicReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // empty block for now
}

void AlgorithmicReverbAudioProcessorEditor::resized()
{
    mainComponent.setBounds(0, 0, getWidth(), getHeight());
}
