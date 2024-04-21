/*
  ==============================================================================

    APF.cpp
    Created: 18 Apr 2024 12:21:13pm
    Author:  Franke Burgarino

  ==============================================================================
*/

#include "APF.h"

APF::APF() {};

APF::~APF() {};

void APF::setFs(float Fs) {
    this->Fs = Fs;
}

void APF::setDepth(float depth) {
    this->depth = depth;
}

float APF::getDepth() {
    return depth;
};

void APF::setSpeed(float speed) {
    this->speed = speed;
    fracDelay.setSpeed(speed);
}

float APF::getSpeed() {
    return speed;
}

void APF::setDelay(float delaySamples) {
    this->delaySamples = delaySamples;
    fracDelay.setDelaySamples(delaySamples);
}

float APF::getDelay() {
    return delaySamples;
}

void APF::setGain(float gain) {
    if (gain >= 0 && gain <= 1) {
        this->gain = gain;
    }
}

float APF::getGain() {
    return gain;
}

float APF::processSample(float x, int channel) {

    delayInput = x - gain * delayOutput;
    delayOutput = fracDelay.processSample(delayInput, channel);

    float y = delayOutput + gain * delayInput;

    return y;

}