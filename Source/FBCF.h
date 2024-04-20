/*
  ==============================================================================

    FBCF.h
    Created: 18 Apr 2024 12:21:00pm
    Author:  Zachary Miller

  ==============================================================================
*/

#pragma once
#include "FractionalDelay.hpp"

class FBCF {
public:
    
    FBCF(); // constructor
    ~FBCF(); // destructor
    
    void setFs(float Fs);
    
    void setDepth(float depth);
    float getDepth();
    
    void setSpeed(float speed);
    float getSpeed();
    
    void setDelay(float delaySamples);
    float getDelay();
    
    void setGain(float gain);
    float getGain();
    
    float processSample(float x, int channel, float g);
    
private:
    
    FractionalDelay fracDelay;
    
    float Fs = 48000;
    
    float depth = 1; // LFO intensity [1-10]
    float speed = 1; // LFO speed (Hz)
    float delay = 10; // delay samples
    float gain = 0.9f; // feedback gain [0-1]
    
    float fbVar = 0.f; // difference equation calc variable
    float y[2] = {0.f}; // fraction delay output
    
    float MAX_BUFFER_SIZE = 96000;

};
