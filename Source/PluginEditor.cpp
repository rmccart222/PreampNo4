#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <BinaryData.h>

PreampNo4AudioProcessorEditor::PreampNo4AudioProcessorEditor(PreampNo4AudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p)
{
	backgroundPanel = juce::ImageCache::getFromMemory(
		BinaryData::background_panel_png,
		BinaryData::background_panel_pngSize);

	knobBody = juce::ImageCache::getFromMemory(
		BinaryData::knob_body_png,
		BinaryData::knob_body_pngSize);

	knobIndicator = juce::ImageCache::getFromMemory(
		BinaryData::knob_indicator_png,
		BinaryData::knob_indicator_pngSize);

	boostOff = juce::ImageCache::getFromMemory(
		BinaryData::boost_off_png,
		BinaryData::boost_off_pngSize);

	boostOn = juce::ImageCache::getFromMemory(
		BinaryData::boost_on_png,
		BinaryData::boost_on_pngSize);

	setSize(661, 273);

	addAndMakeVisible(inputSlider);
	inputSlider.setAlpha(0.0f);
	inputSlider.setSliderStyle(juce::Slider::Rotary);
	inputSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
	inputSlider.setDoubleClickReturnValue(true, 0.0);

	inputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.parameters,
		"input",
		inputSlider);

	addAndMakeVisible(inputLabel);
	inputLabel.setText("Input", juce::dontSendNotification);
	inputLabel.setVisible(false);

	addAndMakeVisible(outputSlider);
	outputSlider.setAlpha(0.0f);
	outputSlider.setSliderStyle(juce::Slider::Rotary);
	outputSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
	outputSlider.setDoubleClickReturnValue(true, 0.0);

	outputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.parameters,
		"output",
		outputSlider);

	addAndMakeVisible(outputLabel);
	outputLabel.setText("Output", juce::dontSendNotification);
	outputLabel.setVisible(false);

	addAndMakeVisible(boostButton);
	boostButton.setButtonText("Boost");
	boostButton.setAlpha(0.0f);

	boostAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		audioProcessor.parameters,
		"boost",
		boostButton);
}

PreampNo4AudioProcessorEditor::~PreampNo4AudioProcessorEditor()
{
}

void PreampNo4AudioProcessorEditor::paint(juce::Graphics& g)
{
	g.drawImage(backgroundPanel, getLocalBounds().toFloat());
}

void PreampNo4AudioProcessorEditor::resized()
{
	inputSlider.setBounds(90, 95, 130, 130);

	outputSlider.setBounds(450, 95, 130, 130);

	boostButton.setBounds(300, 120, 70, 70);
}