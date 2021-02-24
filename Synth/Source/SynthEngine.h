/*
  ==============================================================================

    SynthEngine.h
    Created: 24 Feb 2021 1:00:07pm
    Author:  Phevos

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthEngine : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber)
    {
        return true;
    }

    bool appliesToChannel(int midiNoteNumber)
    {
        return true;
    }

};
