#include "PluginProcessor.h"
#include "PluginEditor.h"

PreampNo4AudioProcessorEditor::PreampNo4AudioProcessorEditor(PreampNo4AudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(400, 300);

    addAndMakeVisible(inputSlider);
    inputSlider.setSliderStyle(juce::Slider::Rotary);
    inputSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    inputSlider.setDoubleClickReturnValue(true, 0.0);

    inputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters,
        "input",
        inputSlider);

    addAndMakeVisible(inputLabel);
    inputLabel.setText("Input", juce::dontSendNotification);

    addAndMakeVisible(outputSlider);
    outputSlider.setSliderStyle(juce::Slider::Rotary);
    outputSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    outputSlider.setDoubleClickReturnValue(true, 0.0);

    outputAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters,
        "output",
        outputSlider);

    addAndMakeVisible(outputLabel);
    outputLabel.setText("Output", juce::dontSendNotification);
}

PreampNo4AudioProcessorEditor::~PreampNo4AudioProcessorEditor()
{
}

void PreampNo4AudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    g.setColour(juce::Colours::white);
    g.setFont(24.0f);

    g.drawFittedText(
        "PREAMP No. 4",
        0,
        20,
        getWidth(),
        30,
        juce::Justification::centred,
        1);

    g.setFont(14.0f);
    g.drawFittedText(
        audioProcessor.namStatus,
        0,
        60,
        getWidth(),
        30,
        juce::Justification::centred,
        1);
}

void PreampNo4AudioProcessorEditor::resized()
{
    inputSlider.setBounds(80, 100, 100, 100);
    inputLabel.setBounds(105, 200, 60, 20);

    outputSlider.setBounds(220, 100, 100, 100);
    outputLabel.setBounds(240, 200, 80, 20);
}