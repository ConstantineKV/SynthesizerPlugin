#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class Envelope : public juce::Component
{
public:
    Envelope(SynthFrameworkAudioProcessor& audioProcessor);
    ~Envelope() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    //void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthFrameworkAudioProcessor& audioProcessor;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderTreeAttack;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderTreeRelease;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderTreeSustain;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sliderTreeDecay;
    juce::Slider attackSlider;
    juce::Slider releaseSlider;
    juce::Slider sustainSlider;
    juce::Slider decaySlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Envelope)
};
