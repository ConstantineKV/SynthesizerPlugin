#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================

class Oscillator : public juce::Component, private juce::ComboBox::Listener
{
public:
    Oscillator(SynthFrameworkAudioProcessor&);
    ~Oscillator() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox*) override;

private:
    juce::ComboBox oscMenu;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthFrameworkAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscillator)
};