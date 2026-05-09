#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

class PreampNo4AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
	PreampNo4AudioProcessorEditor(PreampNo4AudioProcessor&);
	~PreampNo4AudioProcessorEditor() override;

	void paint(juce::Graphics&) override;
	void resized() override;

private:
	PreampNo4AudioProcessor& audioProcessor;

	juce::Slider inputSlider;
	juce::Slider outputSlider;

	juce::Label inputLabel;
	juce::Label outputLabel;

	juce::ToggleButton boostButton;

	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputAttachment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> boostAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PreampNo4AudioProcessorEditor)
};