#include "PluginProcessor.h"
#include "PluginEditor.h"

PreampNo4AudioProcessor::PreampNo4AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    parameters(*this, nullptr, "PARAMETERS",
        {
            std::make_unique<juce::AudioParameterFloat>(
                "input",
                "Input",
                juce::NormalisableRange<float>(-24.0f, 24.0f, 0.1f),
                0.0f),

            std::make_unique<juce::AudioParameterFloat>(
                "output",
                "Output",
                juce::NormalisableRange<float>(-24.0f, 24.0f, 0.1f),
                0.0f)
        })
#endif
{
}

PreampNo4AudioProcessor::~PreampNo4AudioProcessor()
{
}

const juce::String PreampNo4AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PreampNo4AudioProcessor::acceptsMidi() const { return false; }
bool PreampNo4AudioProcessor::producesMidi() const { return false; }
bool PreampNo4AudioProcessor::isMidiEffect() const { return false; }
double PreampNo4AudioProcessor::getTailLengthSeconds() const { return 0.0; }

int PreampNo4AudioProcessor::getNumPrograms() { return 1; }
int PreampNo4AudioProcessor::getCurrentProgram() { return 0; }
void PreampNo4AudioProcessor::setCurrentProgram(int index) {}
const juce::String PreampNo4AudioProcessor::getProgramName(int index) { return {}; }
void PreampNo4AudioProcessor::changeProgramName(int index, const juce::String& newName) {}

void PreampNo4AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
}

void PreampNo4AudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PreampNo4AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono()
        || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
#endif

void PreampNo4AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);

    auto inputDb = parameters.getRawParameterValue("input")->load();
    auto outputDb = parameters.getRawParameterValue("output")->load();

    auto inputGain = juce::Decibels::decibelsToGain(inputDb);
    auto outputGain = juce::Decibels::decibelsToGain(outputDb);

    buffer.applyGain(inputGain);

    // NAM processing will go here later

    buffer.applyGain(outputGain);
}

bool PreampNo4AudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* PreampNo4AudioProcessor::createEditor()
{
    return new PreampNo4AudioProcessorEditor(*this);
}

void PreampNo4AudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
}

void PreampNo4AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PreampNo4AudioProcessor();
}