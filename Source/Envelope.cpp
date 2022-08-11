#include <JuceHeader.h>
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(SynthFrameworkAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);

    //Slider initialization values
    attackSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 20.0, 10.0);
    addAndMakeVisible(&attackSlider);


    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(0.1f);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 20.0, 10.0);
    addAndMakeVisible(&releaseSlider);

    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    sustainSlider.setRange(0.1f, 5000.0f);
    sustainSlider.setValue(0.1f);
    sustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 20.0, 10.0);
    addAndMakeVisible(&sustainSlider);

    decaySlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    decaySlider.setRange(0.1f, 5000.0f);
    decaySlider.setValue(0.1f);
    decaySlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 20.0, 10.0);
    addAndMakeVisible(&decaySlider);

    sliderTreeAttack = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.parameters, "attack", attackSlider);
    sliderTreeRelease = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.parameters, "release", releaseSlider);
    sliderTreeSustain = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.parameters, "sustain", sustainSlider);
    sliderTreeDecay = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.parameters, "decay", decaySlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint(juce::Graphics& g)
{
    juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.drawText("Envelope", titleArea, juce::Justification::centredTop);

    g.drawText("A", 53, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("D", 77, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("S", 103, 150, 20, 20, juce::Justification::centredTop);
    g.drawText("R", 128, 150, 20, 20, juce::Justification::centredTop);


    juce::Rectangle<float> area(25, 25, 150, 150);
    g.setColour(juce::Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Envelope::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(50);

    int sliderWidth = 25;
    int sliderHeight = 175;

    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
}