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
	inputSlider.setAlpha(0.01f);
	inputSlider.setSliderStyle(juce::Slider::LinearVertical);
	inputSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	inputSlider.setMouseDragSensitivity(2700);
	inputSlider.setDoubleClickReturnValue(true, 0.0);

	inputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.parameters,
		"input",
		inputSlider);

	addAndMakeVisible(outputSlider);
	outputSlider.setAlpha(0.01f);
	outputSlider.setSliderStyle(juce::Slider::LinearVertical);
	outputSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
	outputSlider.setMouseDragSensitivity(2700);
	outputSlider.setDoubleClickReturnValue(true, 0.0);

	outputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
		audioProcessor.parameters,
		"output",
		outputSlider);

	addAndMakeVisible(boostButton);
	boostButton.setButtonText("Boost");
	boostButton.setAlpha(0.01f);

	boostAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
		audioProcessor.parameters,
		"boost",
		boostButton);

	inputSlider.onValueChange = [this]() { repaint(); };
	outputSlider.onValueChange = [this]() { repaint(); };
	boostButton.onClick = [this]() { repaint(); };

	inputSlider.onDragStart = [this]()
		{
			showingInputValue = true;
			repaint();
		};

	inputSlider.onDragEnd = [this]()
		{
			showingInputValue = false;
			repaint();
		};

	outputSlider.onDragStart = [this]()
		{
			showingOutputValue = true;
			repaint();
		};

	outputSlider.onDragEnd = [this]()
		{
			showingOutputValue = false;
			repaint();
		};
}

PreampNo4AudioProcessorEditor::~PreampNo4AudioProcessorEditor()
{
}

static float valueToAngle(float value, float minValue, float maxValue)
{
	const auto startAngle = juce::degreesToRadians(-120.0f);
	const auto endAngle = juce::degreesToRadians(120.0f);
	const auto normalised = juce::jmap(value, minValue, maxValue, 0.0f, 1.0f);

	return juce::jmap(normalised, 0.0f, 1.0f, startAngle, endAngle);
}

void PreampNo4AudioProcessorEditor::paint(juce::Graphics& g)
{
	g.drawImage(backgroundPanel, getLocalBounds().toFloat());

	const int knobSize = 130;

	const int inputX = 75;
	const int inputY = 98;

	const int outputX = 450;
	const int outputY = 99;

	const int boostX = 287;
	const int boostY = 125;
	const int boostSize = 80;

	g.drawImage(knobBody,
		inputX, inputY, knobSize, knobSize,
		0, 0,
		knobBody.getWidth(),
		knobBody.getHeight());

	g.drawImage(knobBody,
		outputX, outputY, knobSize, knobSize,
		0, 0,
		knobBody.getWidth(),
		knobBody.getHeight());

	const auto inputValue = audioProcessor.parameters.getRawParameterValue("input")->load();
	const auto inputAngle = valueToAngle(inputValue, -20.0f, 20.0f);

	{
		juce::Graphics::ScopedSaveState inputState(g);

		g.addTransform(juce::AffineTransform::rotation(
			inputAngle,
			inputX + knobSize * 0.5f,
			inputY + knobSize * 0.5f));

		g.drawImage(knobIndicator,
			inputX, inputY, knobSize, knobSize,
			0, 0,
			knobIndicator.getWidth(),
			knobIndicator.getHeight());
	}

	const auto outputValue = audioProcessor.parameters.getRawParameterValue("output")->load();
	const auto outputAngle = valueToAngle(outputValue, -40.0f, 40.0f);

	{
		juce::Graphics::ScopedSaveState outputState(g);

		g.addTransform(juce::AffineTransform::rotation(
			outputAngle,
			outputX + knobSize * 0.5f,
			outputY + knobSize * 0.5f));

		g.drawImage(knobIndicator,
			outputX, outputY, knobSize, knobSize,
			0, 0,
			knobIndicator.getWidth(),
			knobIndicator.getHeight());
	}

	auto& boostImage = boostButton.getToggleState() ? boostOn : boostOff;

	g.drawImage(boostImage,
		boostX, boostY, boostSize, boostSize,
		0, 0,
		boostImage.getWidth(),
		boostImage.getHeight());

	if (showingInputValue)
	{
		const auto value = audioProcessor.parameters
			.getRawParameterValue("input")->load();

		g.setColour(juce::Colour(0xff2B2926));
		g.fillRoundedRectangle(95.0f, 55.0f, 90.0f, 28.0f, 6.0f);

		g.setColour(juce::Colour(0xffE3DED4));
		g.setFont(16.0f);

		g.drawFittedText(
			juce::String(value, 1) + " dB",
			95, 55, 90, 28,
			juce::Justification::centred,
			1);
	}

	if (showingOutputValue)
	{
		const auto value = audioProcessor.parameters
			.getRawParameterValue("output")->load();

		g.setColour(juce::Colour(0xff2B2926));
		g.fillRoundedRectangle(470.0f, 55.0f, 90.0f, 28.0f, 6.0f);

		g.setColour(juce::Colour(0xffE3DED4));
		g.setFont(16.0f);

		g.drawFittedText(
			juce::String(value, 1) + " dB",
			470, 55, 90, 28,
			juce::Justification::centred,
			1);
	}
}

void PreampNo4AudioProcessorEditor::resized()
{
	inputSlider.setBounds(75, 98, 130, 130);
	outputSlider.setBounds(450, 99, 130, 130);
	boostButton.setBounds(287, 125, 80, 80);
}