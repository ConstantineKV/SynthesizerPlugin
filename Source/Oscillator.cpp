#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(SynthFrameworkAudioProcessor& p) : audioProcessor(p)
{
    setSize(200, 200);

    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);

    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);

    waveSelection = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.parameters, "wavetype", oscMenu);
    oscMenu.setJustificationType(juce::Justification::centred);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(area.removeFromTop(20));
}

void Oscillator::comboBoxChanged(juce::ComboBox* box)
{
}