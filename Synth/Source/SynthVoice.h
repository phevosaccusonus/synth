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
    bool canPlaySound(SynthEngine* sound)
    {
        return dynamic_cast <SynthEngine*>(sound) != nullptr;
    }

    void startNote(int midiNoteNumber, float velocity, SynthEngine* sound, int currentPitchWheelPosition)
    {

    }

    void stopNote(float velocity, bool allowTailOff)
    {

    }

    void pitchWheelMoved(int newpitchWheelValue)
    {

    }

    void controllerMoved(int controllerNumber, int newControllerValue)
    {

    }

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {

    }


};
