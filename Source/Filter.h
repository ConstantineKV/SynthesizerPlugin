#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================

class Filter : public juce::Component
{
public:
    Filter(SynthFrameworkAudioProcessor& audioProcessor);
    ~Filter() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthFrameworkAudioProcessor& audioProcessor;
    juce::Slider filterCutoff;
    juce::Slider filterRes;
    juce::ComboBox filterMenu;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> resVal;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};