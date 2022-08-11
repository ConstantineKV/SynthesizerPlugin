/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessorEditor::SynthFrameworkAudioProcessorEditor(SynthFrameworkAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), oscGUI(p), envGUI(p), filterGUI(p)
{
    setSize(600, 200);

    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGUI);
}

SynthFrameworkAudioProcessorEditor::~SynthFrameworkAudioProcessorEditor()
{
}

//==============================================================================
void SynthFrameworkAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void SynthFrameworkAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();

    const int componentWidth = 200;
    const int componentHeight = 200;
    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
}