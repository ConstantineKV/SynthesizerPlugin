/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthFrameworkAudioProcessor::SynthFrameworkAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    attackTime(0.1f), parameters(*this, nullptr)
#endif
{
    juce::NormalisableRange<float> attackParam(0.1f, 5000.0f);
    juce::NormalisableRange<float> releaseParam(0.1f, 5000.0f);
    juce::NormalisableRange<float> sustainParam(0.0f, 1.0f);
    juce::NormalisableRange<float> decayParam(0.1f, 1000.0f);
    juce::NormalisableRange<float> wavetypeParam(0.0f, 2.0f);

    juce::NormalisableRange<float> filterTypeVal(0.0f, 2.0f);
    juce::NormalisableRange<float> filterParam(20.0f, 10000.0f);
    juce::NormalisableRange<float> resVal(1.0f, 5.0f);

    parameters.createAndAddParameter("attack", "Attack", "Attack", attackParam, 0.1f, nullptr, nullptr);
    parameters.createAndAddParameter("release", "Release", "Release", releaseParam, 0.1f, nullptr, nullptr);
    parameters.createAndAddParameter("sustain", "Sustain", "Sustain", sustainParam, 0.5f, nullptr, nullptr);
    parameters.createAndAddParameter("decay", "Decay", "Decay", decayParam, 0.0f, nullptr, nullptr);
    parameters.createAndAddParameter("wavetype", "WaveType", "Wavetype", wavetypeParam, 0, nullptr, nullptr);
    parameters.createAndAddParameter("filterCutOff", "filterCutOff", "filterCutOff", filterParam, 400.0f, nullptr, nullptr);
    parameters.createAndAddParameter("filterRes", "filterRes", "filterRes", resVal, 1.0f, nullptr, nullptr);
    parameters.createAndAddParameter("filterType", "filterType", "filterType", filterTypeVal, 0, nullptr, nullptr);

    mySynth.clearVoices();
    for (int i = 0; i < 5; ++i)
    {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());

    std::cout << "Test" << std::endl;

}

SynthFrameworkAudioProcessor::~SynthFrameworkAudioProcessor()
{
}

//==============================================================================
const juce::String SynthFrameworkAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthFrameworkAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SynthFrameworkAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool SynthFrameworkAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double SynthFrameworkAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthFrameworkAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthFrameworkAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthFrameworkAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String SynthFrameworkAudioProcessor::getProgramName(int index)
{
    return {};
}

void SynthFrameworkAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void SynthFrameworkAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{

    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void SynthFrameworkAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthFrameworkAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void SynthFrameworkAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    std::cout << attackTime << std::endl;

    for (int i = 0; i < mySynth.getNumVoices(); ++i)
    {
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
        {
            myVoice->setParam(parameters.getRawParameterValue("attack")->load(),
                parameters.getRawParameterValue("release")->load(),
                parameters.getRawParameterValue("sustain")->load(),
                parameters.getRawParameterValue("decay")->load());

            myVoice->setOscType(parameters.getRawParameterValue("wavetype")->load());
            myVoice->setFilterParams(parameters.getRawParameterValue("filterType")->load(),
                parameters.getRawParameterValue("filterCutOff")->load(),
                parameters.getRawParameterValue("filterRes")->load());

        }
    }

    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SynthFrameworkAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthFrameworkAudioProcessor::createEditor()
{
    return new SynthFrameworkAudioProcessorEditor(*this);
}

//==============================================================================
void SynthFrameworkAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
}

void SynthFrameworkAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthFrameworkAudioProcessor();
}