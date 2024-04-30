/*
  ==============================================================================

    SliderWidgets.h
    Created: 20 Apr 2024 3:01:50pm
    Author:  Raymond Plasse

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../SharedImages.h"

class VertSlider : public juce::Slider {
public:
    VertSlider(SharedImages* i) : sliderImage(i->getVertSlider()) {
        // empty block
    }
    
    ~VertSlider() {
        // empty block
    }
    
    void paint(juce::Graphics& g) override {
        const double fractRotation = (getValue() - getMinimum()) / (getMaximum() - getMinimum());
        
        int frameIndex = floor(fractRotation * (numFrames - 1));
        
        const int startY = frameIndex * frameHeight;
        
        g.drawImage(sliderImage, 0, 0, getWidth(), getHeight(), 0, startY, frameWidth, frameHeight);
    }
    
private:
    juce::Image& sliderImage;
    int numFrames = 129;
    int frameHeight = 394;
    int frameWidth = 154;
};

class HorzSlider : public juce::Slider {
public:
    HorzSlider(SharedImages* i) : sliderImage(i->getHorzSlider()) {
        // empty block
    }
    
    ~HorzSlider() {
        // empty block
    }
    
    void paint(juce::Graphics& g) override {
        const double fractRotation = (getValue() - getMinimum()) / (getMaximum() - getMinimum());
        
        int frameIndex = floor(fractRotation * (numFrames - 1));
        
        const int startY = frameIndex * frameHeight;
        
        g.drawImage(sliderImage, 0, 0, getWidth(), getHeight(), 0, startY, frameWidth, frameHeight);
    }
    
private:
    juce::Image& sliderImage;
    int numFrames = 129;
    int frameHeight = 154;
    int frameWidth = 394;
};
