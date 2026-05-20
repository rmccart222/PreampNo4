#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include "NAM/get_dsp.h"

class PreampNo4AudioProcessor : public juce::AudioProcessor
{
public:
	PreampNo4AudioProcessor();
	~PreampNo4AudioProcessor() override;

	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

	void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

	juce::AudioProcessorEditor* createEditor() override;
	bool hasEditor() const override;

	const juce::String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;

	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const juce::String getProgramName(int index) override;
	void changeProgramName(int index, const juce::String& newName) override;

	void getStateInformation(juce::MemoryBlock& destData) override;
	void setStateInformation(const void* data, int sizeInBytes) override;

	juce::AudioProcessorValueTreeState parameters;
	juce::String namStatus = "NAM not loaded";

	double currentSampleRate = 48000.0;
	bool sampleRateIs48k = true;

private:
	std::unique_ptr<nam::DSP> defaultModel;
	std::unique_ptr<nam::DSP> boostModel;

	bool modelsLoaded = false;

	std::vector<double> namInputBuffer;
	std::vector<double> namOutputBuffer;

	std::array<double*, 1> namInputPointers;
	std::array<double*, 1> namOutputPointers;

	std::vector<double> resampledInputBuffer;
	std::vector<double> resampledOutputBuffer;

	std::array<double*, 1> resampledInputPointers;
	std::array<double*, 1> resampledOutputPointers;

	double internalModelSampleRate = 48000.0;
	bool needsResampling = false;

	juce::LagrangeInterpolator inputResampler;
	juce::LagrangeInterpolator outputResampler;

	std::vector<float> hostMonoFloatBuffer;
	std::vector<float> resampledInputFloatBuffer;
	std::vector<float> resampledOutputFloatBuffer;
	std::vector<float> hostOutputFloatBuffer;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PreampNo4AudioProcessor)
};