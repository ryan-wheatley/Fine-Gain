
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================

class FineGainAudioProcessorEditor  : public AudioProcessorEditor,
                                     public Slider::Listener
                                     
{
public:
    FineGainAudioProcessorEditor (FineGainAudioProcessor&);
    ~FineGainAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;

private:
   
    Slider mGainSlider;


    FineGainAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FineGainAudioProcessorEditor)
};
