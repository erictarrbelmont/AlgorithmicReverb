/*
  ==============================================================================

    APF.h
    Created: 18 Apr 2024 12:21:13pm
    Author:  Franke Burgarino

  ==============================================================================
*/

#pragma once
#include "FractionalDelay.hpp"

class APF {

public: 

    APF();
    ~APF();

    void setFs(float Fs);

    void setDepth(float depth);
    float getDepth();

    void setSpeed(float speed);
    float getSpeed();

    void setDelay(float delaySamples);
    float getDelay();

    void setGain(float gain);
    float getGain();

    float processSample(float x, int channel);

private:

    float Fs;
    float delaySamples; // delay time in samples
    float gain;

    float depth; // LFO depth for FractionalDelay
    float speed; // LFO speed (Hz) for FractionalDelay
    
    FractionalDelay fracDelay;

    float delayInput;
    float delayOutput = 0.f;

};