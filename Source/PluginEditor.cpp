
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FineGainAudioProcessorEditor::FineGainAudioProcessorEditor (FineGainAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

    mGainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    mGainSlider.setColour(Slider::thumbColourId, Colours::aliceblue);

    mGainSlider.setTextBoxStyle(Slider::TextBoxAbove, false, 50,20);
    mGainSlider.setColour(Slider::backgroundColourId, Colours::greenyellow);
    mGainSlider.setColour(Slider::textBoxBackgroundColourId, Colours::lightgrey);
    mGainSlider.setColour(Slider::textBoxOutlineColourId, Colours::black);
    mGainSlider.setColour(Slider::textBoxTextColourId, Colours::black);

    mGainSlider.setRange(-2.0f, 2.0f, 0.01f);
    mGainSlider.setValue(0.5f);
    mGainSlider.addListener(this);

    addAndMakeVisible(mGainSlider);

    setSize (125, 300);
}

FineGainAudioProcessorEditor::~FineGainAudioProcessorEditor()
{
}

//==============================================================================
void FineGainAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(Colours::lightslategrey);
    mGainSlider.setBounds(getWidth() / 2 - 50, getHeight() / 2 - 125, 100, 250);
}

void FineGainAudioProcessorEditor::resized()
{
   
}

void FineGainAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &mGainSlider) {
        processor.mGain = mGainSlider.getValue();
    }
}