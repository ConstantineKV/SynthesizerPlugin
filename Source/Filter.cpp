#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(SynthFrameworkAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);

    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("High Pass", 2);
    filterMenu.addItem("Band Pass", 3);

    filterMenu.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(&filterMenu);
    filterTypeVal = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.parameters, "filterType", filterMenu);

    filterCutoff.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterCutoff.setRange(20.0f, 10000.0f);
    filterCutoff.setValue(400.0f);
    filterCutoff.setTextBoxStyle(juce::Slider::NoTextBox, true, 20.0, 10.0);
    filterCutoff.setSkewFactorFromMidPoint(1000.0);
    filterVal = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "filterCutOff", filterCutoff);
    addAndMakeVisible(&filterCutoff);


    filterRes.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    filterRes.setRange(1.0f, 5.0f);
    filterRes.setValue(1.0f);
    filterRes.setTextBoxStyle(juce::Slider::NoTextBox, true, 20.0, 10.0);
    resVal = std::make_unique< juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "filterRes", filterRes);
    addAndMakeVisible(&filterRes);
}

Filter::~Filter()
{
}

void Filter::paint(juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);
    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colours::white);
    g.drawText("Filter", titleArea, juce::Justification::centredTop);

    juce::Rectangle<float> area(25, 25, 150, 150);

    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    filterMenu.setBounds(area.removeFromTop(20));
    filterCutoff.setBounds(30, 100, 70, 70);
    filterRes.setBounds(100, 100, 70, 70);
}
