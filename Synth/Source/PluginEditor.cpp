/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthAudioProcessorEditor::SynthAudioProcessorEditor (SynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE", releaseSlider);

    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);

    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    decaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);

    for (int i = 0; i < adsrNames.size(); i++)
    {
        macroLabel.push_back(std::unique_ptr<juce::Label>(new juce::Label(juce::String(adsrNames[i]), TRANS(adsrNames[i]))));
        macroLabel[i]->setFont(juce::Font{ "Muli", "Regular", 20.0f });
        macroLabel[i]->setJustificationType(juce::Justification::centredLeft);
        macroLabel[i]->setEditable(false, false, false);
        macroLabel[i]->setColour(juce::Label::textColourId, juce::Colour::fromRGB(255, 244, 230));
        macroLabel[i]->setColour(juce::TextEditor::textColourId, juce::Colours::black);
        macroLabel[i]->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));
        addAndMakeVisible(macroLabel[i].get());

    }

    headerLabel.reset(new juce::Label("headerLabel",
        TRANS("Basic pH Synth")));
    addAndMakeVisible(headerLabel.get());
    headerLabel->setFont(juce::Font{ "Muli", "Bold", 30.0f });
    headerLabel->setJustificationType(juce::Justification::centredLeft);
    headerLabel->setEditable(false, false, false);
    headerLabel->setColour(juce::Label::textColourId, juce::Colour::fromRGB(255, 244, 230));
    headerLabel->setColour(juce::TextEditor::textColourId, juce::Colours::black);
    headerLabel->setColour(juce::TextEditor::backgroundColourId, juce::Colour(0x00000000));

    setSize(600, 400);
}

SynthAudioProcessorEditor::~SynthAudioProcessorEditor()
{
}

//==============================================================================
void SynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void SynthAudioProcessorEditor::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getWidth() / 4 - padding;
    const auto sliderStartX = 0;
    const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

    macroLabel[0]->setBounds(sliderStartX + 35, 80, 100, 24);
    macroLabel[1]->setBounds(attackSlider.getRight() + 45, 80, 100, 24);
    macroLabel[2]->setBounds(decaySlider.getRight() + 40, 80, 100, 24);
    macroLabel[3]->setBounds(sustainSlider.getRight() + 40, 80, 100, 24);

    headerLabel->setBounds(200, 10, 300, 50);
}

void SynthAudioProcessorEditor::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
