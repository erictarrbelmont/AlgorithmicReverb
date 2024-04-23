/*
  ==============================================================================

    SchroederReverb.cpp
    Created: 18 Apr 2024 12:20:43pm
    Author:  Eric Tarr

  ==============================================================================
*/

#include "SchroederReverb.h"

void SchroederReverb::processSample (float x, const int c) {
    
    // Work in progress
    
    // Setting gain parameter for the FBCF blocks
    firstDelayBlock.setGain(FBGain);
    secondDelayBlock.setGain(FBGain);
    thirdDelayBlock.setGain(FBGain);
    fourthDelayBlock.setGain(FBGain);
    
    // Processing the sample through each of the FBCF blocks in parallel
    float a = firstDelayBlock.processSample(x, c, FBGain);
    float b = secondDelayBlock.processSample(x);
    float c = thirdDelayBlock.processSample(x);
    float d = fourthDelayBlock.processSample(x);
    
    // Summing together all the parts
    float processedFBCF = a + b + c + d;
    
    // Setting the gain parameter for the APF blocks
    firstAPFFilter.setGain(APGain);
    secondAPFFilter.setGain(APGain);
    
    // Processing the combined sum of the FBCF blocks through the APF in series
    float e = firstAPFFilter.processSample(processedFBCF);
    float processedAPF = secondAPFFilter.processSample(e);
    
}

void SchroederReverb::process (float * buffer, const int N, const int c) {
    for (int n = 0 ; n < N ; n++) {
        float x = buffer[n];
        float y = processSample(x, c);
}
