/*
  ==============================================================================

    SynthVoice.h
    Created: 24 Feb 2021 1:00:41pm
    Author:  Phevos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthEngine.h"


class SynthVoice : public juce::SynthesiserVoice
{
public:

    bool canPlaySound(juce::SynthesiserSound* sound) override;

    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void controllerMoved(int controllerNumber, int newControllerValue) override;

    void pitchWheelMoved(int newPitchWheelValue) override;

    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);

    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

private:

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParameters;
    juce::dsp::Oscillator<float> osc{ [](float x) { return x < 0.0f ? -1.0f : 1.0f; }, 200 };
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };

    // return std::sin (x); //Sine Wave
    // return x / MathConstants<float>::pi; // Saw Wave
    // return x < 0.0f ? -1.0f : 1.0f;  // Square Wave

};
