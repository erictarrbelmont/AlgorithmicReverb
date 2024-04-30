/*
  ==============================================================================

    MainComponent.h
    Created: 20 Apr 2024 3:01:23pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../SharedImages.h"
#include "SliderWidgets.h"

class MainComponent : public juce::Component {
public:
    MainComponent(AlgorithmicReverbAudioProcessor&);
    ~MainComponent() override;
    
    void paint(juce::Graphics&) override;
    void resized() override;
        
private:
    AlgorithmicReverbAudioProcessor&    audioProcessor;
    SharedImages*                       sharedImagesPtr;
    VertSlider                          timeVertSlider;
    VertSlider                          freqVertSlider;
    HorzSlider                          diffHorzSlider;
    juce::Slider                        mixRotarySlider;
    juce::Label                         timeSliderLabel;
        
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
