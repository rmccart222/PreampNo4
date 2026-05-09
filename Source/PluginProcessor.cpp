#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <filesystem>
#include "NAM/wavenet/model.h"

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
				juce::NormalisableRange<float>(-20.0f, 20.0f, 0.1f),
				0.0f),

			std::make_unique<juce::AudioParameterFloat>(
				"output",
				"Output",
				juce::NormalisableRange<float>(-40.0f, 40.0f, 0.1f),
				0.0f),

			std::make_unique<juce::AudioParameterBool>(
				"boost",
				"Boost",
				false)
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
	juce::ignoreUnused(sampleRate, samplesPerBlock);

	namInputBuffer.resize((size_t)samplesPerBlock);
	namOutputBuffer.resize((size_t)samplesPerBlock);

	namInputPointers[0] = namInputBuffer.data();
	namOutputPointers[0] = namOutputBuffer.data();

	if (!modelsLoaded)
	{
		try
		{
			const auto defaultModelPath = std::filesystem::path(
				"C:/Dev/Projects/PreampNo4/Models/preamp_no4_default.nam"
			);

			const auto boostModelPath = std::filesystem::path(
				"C:/Dev/Projects/PreampNo4/Models/preamp_no4_boost.nam"
			);

			try
			{
				static nam::ConfigParserHelper forceWaveNetRegistration(
					"WaveNet",
					nam::wavenet::create_config
				);
			}
			catch (const std::exception&)
			{
			}

			defaultModel = nam::get_dsp(defaultModelPath);
			boostModel = nam::get_dsp(boostModelPath);

			modelsLoaded = (defaultModel != nullptr && boostModel != nullptr);

			namStatus = modelsLoaded ? "NAM models loaded successfully"
				: "NAM model load failed";
		}
		catch (const std::exception& e)
		{
			modelsLoaded = false;
			namStatus = "NAM load exception: " + juce::String(e.what());
		}
	}
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
	juce::ScopedNoDenormals noDenormals;

	const auto numSamples = buffer.getNumSamples();
	const auto numChannels = buffer.getNumChannels();

	auto inputDb = parameters.getRawParameterValue("input")->load();
	auto outputDb = parameters.getRawParameterValue("output")->load();

	auto inputGain = juce::Decibels::decibelsToGain(inputDb);
	auto outputGain = juce::Decibels::decibelsToGain(outputDb);

	buffer.applyGain(inputGain);

	auto boostOn = parameters.getRawParameterValue("boost")->load() > 0.5f;
	auto* activeModel = boostOn ? boostModel.get() : defaultModel.get();

	if (modelsLoaded && activeModel != nullptr)
	{
		for (int sample = 0; sample < numSamples; ++sample)
		{
			float monoSample = 0.0f;

			for (int channel = 0; channel < numChannels; ++channel)
				monoSample += buffer.getSample(channel, sample);

			monoSample /= (float)numChannels;

			namInputBuffer[(size_t)sample] = monoSample;
		}

		activeModel->process(namInputPointers.data(), namOutputPointers.data(), numSamples);

		for (int channel = 0; channel < numChannels; ++channel)
		{
			auto* channelData = buffer.getWritePointer(channel);

			for (int sample = 0; sample < numSamples; ++sample)
				channelData[sample] = namOutputBuffer[(size_t)sample];
		}
	}

	const auto hiddenOutputTrim = juce::Decibels::decibelsToGain(-6.0f);
	buffer.applyGain(outputGain * hiddenOutputTrim);
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