/*
  ==============================================================================

    MainComponent.cpp
    Created: 20 Apr 2024 3:01:23pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#include "MainComponent.h"

MainComponent::MainComponent(AlgorithmicReverbAudioProcessor& p) :
    audioProcessor          (p),
    sharedImagesPtr         (audioProcessor.getSharedImagesPtr()),
    timeVertSlider          (sharedImagesPtr),
    freqVertSlider          (sharedImagesPtr),
    diffHorzSlider          (sharedImagesPtr)
{
    getLookAndFeel().setDefaultSansSerifTypefaceName("Futura");
    
    getLookAndFeel().setColour(juce::Slider::textBoxOutlineColourId, juce::Colour(56,56,59));
    getLookAndFeel().setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour(56,56,59).darker(0.5f));
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colour(75,108,146));
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour(144,144,144));
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(26,26,26));
    getLookAndFeel().setColour(juce::Label::backgroundColourId, juce::Colour(56,56,59).darker(0.5f));
    getLookAndFeel().setColour(juce::Label::outlineColourId, juce::Colour(56,56,59));
           
    addAndMakeVisible(timeVertSlider);
    addAndMakeVisible(freqVertSlider);
    addAndMakeVisible(diffHorzSlider);
    addAndMakeVisible(mixRotarySlider);
}

MainComponent::~MainComponent() {
    // empty block
}

void MainComponent::paint(juce::Graphics& g) {
    int width = getWidth();
    int height = getHeight();
    
    g.drawImage(sharedImagesPtr->getBackgroundImage(), 0, 0, width, height, 0, 0, 2000, 1400);
    
    g.setColour(juce::Colours::azure);

    g.setFont(70.f);
    g.drawText("schroeder", 300, 40, 400, 60, juce::Justification::centred, false);
    g.drawText("algo-verb", 300, 100, 400, 60, juce::Justification::centred, false);

    g.setFont(40.f);
    g.drawText("time", 150, 235, 100, 40, juce::Justification::centred, false);
    g.drawText("diff", 450, 305, 100, 40, juce::Justification::centred, false);
    g.drawText("freq", 750, 235, 100, 40, juce::Justification::centred, false);
    g.drawText("mix", 450, 498, 100, 40, juce::Justification::centred, false);
}

void MainComponent::resized() {
    timeVertSlider.setBounds(143, 259, 114, 284);
    timeVertSlider.setRange(10.f,50.f);
    timeVertSlider.setSkewFactorFromMidPoint(30.f);
    timeVertSlider.setTextValueSuffix(" ms");
    timeVertSlider.setSliderStyle(juce::Slider::LinearVertical);
    timeVertSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 35);
    timeVertSlider.setNumDecimalPlacesToDisplay(1);
    
    freqVertSlider.setBounds(743, 259, 114, 284);
    freqVertSlider.setRange(20.f,250.f);
    freqVertSlider.setSkewFactorFromMidPoint(145.f);
    freqVertSlider.setTextValueSuffix(" hz");
    freqVertSlider.setSliderStyle(juce::Slider::LinearVertical);
    freqVertSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 35);
    freqVertSlider.setNumDecimalPlacesToDisplay(1);
    
    diffHorzSlider.setBounds(358, 329, 284, 114);
    diffHorzSlider.setRange(0.f,100.f);
    diffHorzSlider.setSkewFactorFromMidPoint(50.f);
    diffHorzSlider.setTextValueSuffix(" %");
    diffHorzSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    diffHorzSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 35);
    diffHorzSlider.setNumDecimalPlacesToDisplay(1);
    
    mixRotarySlider.setBounds(435, 535, 130, 130);
    mixRotarySlider.setRange(0.f,100.f);
    mixRotarySlider.setSkewFactorFromMidPoint(50.f);
    mixRotarySlider.setTextValueSuffix(" %");
    mixRotarySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mixRotarySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 35);
    mixRotarySlider.setNumDecimalPlacesToDisplay(1);
}
