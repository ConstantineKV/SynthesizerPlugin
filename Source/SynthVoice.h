#pragma once
#include <JuceHeader.h>

#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    void setParam(float attack, float release, float sustain, float decay)
    {
        env1.setAttack(static_cast<double>(attack));
        env1.setRelease(static_cast<double>(release));
        env1.setSustain(static_cast<double>(sustain));
        env1.setDecay(static_cast<double>(decay));
    }

    //===============================================================
    double calculateWaveByEnvelope()
    {
        return env1.adsr(calculateWaveByOscType(), env1.trigger) * level;
    }


    //===============================================================
    void setOscType(float selection)
    {
        std::cout << selection << std::endl;
        theWave = selection;
    }

    //===============================================================
    double calculateWaveByOscType()
    {
        if (theWave == 0)
        {
            return osc1.sinewave(frequency);
        }

        if (theWave == 1)
        {
            return osc1.saw(frequency);
        }

        if (theWave == 2)
        {
            return osc1.square(frequency);
        }
        else
        {
            return osc1.sinewave(frequency);
        }

    }

    //===============================================================

    void setFilterParams(float filterType, float filterCutoff, float filterRes)
    {
        filterChoice = filterType;
        cutoff = filterCutoff;
        resonance = filterRes;
    }

    //===============================================================


    double calculateWaveByFilter()
    {
        if (filterChoice == 0)
        {
            return filter1.lores(calculateWaveByEnvelope(), cutoff, resonance);
        }

        if (filterChoice == 1)
        {
            return filter1.hipass(calculateWaveByEnvelope(), cutoff);
        }

        if (filterChoice == 2)
        {
            return filter1.bandpass(calculateWaveByEnvelope(), cutoff, resonance);
        }
    }

    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        std::cout << midiNoteNumber << std::endl;
    }

    void stopNote(float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;

        if (velocity == 0)
            clearCurrentNote();
    }

    void pitchWheelMoved(int newPitchWheelValue)
    {
        return;
    }

    void controllerMoved(int controllerNumber, int newCOntrollerValue)
    {

    }

    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {

        for (int sample = 0; sample < numSamples; ++sample)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, calculateWaveByFilter());
            }

            ++startSample;
        }
    }

    double level;
    double frequency;
    int theWave;

    int filterChoice;
    float cutoff;
    float resonance;

    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};