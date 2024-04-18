/*
  ==============================================================================

    SchroederReverb.h
    Created: 18 Apr 2024 12:20:43pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once
#pragma once
#include "FBCF.h"
#include "APF.h"

class SchroederReverb {
    
public:
    
    // Standard prepare function
    void prepare(double sampleRate){
        Fs = sampleRate;
    }
    
    // Setting the gain associated with the FBCF blocks.
    void setFBGain(float inputGain) {
        FBGain = inputGain;
    }
    
    // Setting the gain associated with the APF blocks
    void setAPGain(float inputGain) {
        APGain = inputGain;
    }
    
    // Processing by sample
    void processSample (float x, const int c) {}
    
    // Processing by buffer
    void process (float * buffer, const int N, const int c) {}
    
    
private:
    
    double Fs = 48000.f;
    
    float FBGain = 0.f; // Affects length of reverb, one value will be applied to all intances of FBCF
    float APGain = 0.f; // Affects Diffusion, one value will be applied to all intances of APF
    
    // Intances for each FBCF and APF filters labeled accordingly
    FBCF firstDelayBlock;
    FBCF secondDelayBlock;
    FBCF thirdDelayBlock;
    FBCF fourthDelayBlock;
    
    APF firstAPFFilter;
    APF secondAPFFilter;
    
};
