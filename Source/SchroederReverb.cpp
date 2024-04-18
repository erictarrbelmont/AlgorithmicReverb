/*
  ==============================================================================

    SchroederReverb.cpp
    Created: 18 Apr 2024 12:20:43pm
    Author:  Eric Tarr

  ==============================================================================
*/

#include "SchroederReverb.h"

void processSample (float x, const int c) {
    
    // Work in progress
    
    // Setting gain parameter for the FBCF blocks
    firstDelayBlock.setFBGain(FBGain);
    secondDelayBlock.setFBGain(FBGain);
    thirdDelayBlock.setFBGain(FBGain);
    fourthDelayBlock.setFBGain(FBGain);
    
    // Processing the sample through each of the FBCF blocks in parallel
    float a = firstDelayBlock.processSample(x);
    float b = secondDelayBlock.processSample(x);
    float c = thirdDelayBlock.processSample(x);
    float d = fourthDelayBlock.processSample(x);
    
    // Summing together all the parts
    float processedFBCF = a + b + c + d;
    
    // Setting the gain parameter for the APF blocks
    firstAPFFilter.setAPGain(APGain);
    secondAPFFilter.setAPGain(APGain);
    
    // Processing the combined sum of the FBCF blocks through the APF in series
    float e = firstAPFFilter.processSample(processedFBCF);
    float processedAPF = secondAPFFilter.processSample(e);
    
}

void process (float * buffer, const int N, const int c) {
    for (int n = 0 ; n < N ; n++) {
        float x = buffer[n];
        float y = processSample(x, c);
}
