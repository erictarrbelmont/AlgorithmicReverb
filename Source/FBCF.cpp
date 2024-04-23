/*
  ==============================================================================

    FBCF.cpp
    Created: 18 Apr 2024 12:21:00pm
    Author:  Zachary Miller

  ==============================================================================
*/

#include "FBCF.h"

FBCF::FBCF(){
};

FBCF::~FBCF(){
};

void FBCF::setFs(float Fs) {
    this->Fs = Fs;
}

void FBCF::setDepth(float depth) {
    if (depth >= 1.f && depth <= 10.f) {
        this->depth = depth;
    }
}

float FBCF::getDepth(){
    return depth;
};

void FBCF::setSpeed(float speed) {
    if (speed >= 0.1f && speed <= 10.f) {
        this->speed = speed;
    }
}

float FBCF::getSpeed() {
    return speed;
}

void FBCF::setDelay(float delaySamples) {
    if (delaySamples >= 1 && delaySamples <= MAX_BUFFER_SIZE) {
        this->delay = delaySamples;
    }
}

float FBCF::getDelay() {
    return delay;
}

void FBCF::setGain(float gain) {
    if (gain >= 0 && gain <= 1) {
        this->gain = gain;
    }
}

float FBCF::getGain() {
    return gain;
}

float FBCF::processSample(float x, int channel) {
    
    fbVar = x - gain * y[channel];
    y[channel] = fracDelay.processSample(fbVar,channel);
    return y[channel];
    
}
