/*
  ==============================================================================

    FBCF.h
    Created: 18 Apr 2024 12:21:00pm
    Author:  Eric Tarr

  ==============================================================================
*/

#pragma once
#include "FractionalDelay.hpp"

class FBCF {
public:
    
    float processSample(float x, int channel);
    
private:
    
    FractionalDelay fracDelay;
    
};
