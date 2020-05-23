#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FineGainAudioProcessor::FineGainAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

FineGainAudioProcessor::~FineGainAudioProcessor()
{
}

//==============================================================================
const String FineGainAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FineGainAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FineGainAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FineGainAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FineGainAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FineGainAudioProcessor::getNumPrograms()
{
    return 1;   
}

int FineGainAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FineGainAudioProcessor::setCurrentProgram (int index)
{
}

const String FineGainAudioProcessor::getProgramName (int index)
{
    return {};
}

void FineGainAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FineGainAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
}

void FineGainAudioProcessor::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FineGainAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FineGainAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            channelData[sample] *= (1+mGain*10/100);
        }
    }
}

//==============================================================================
bool FineGainAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* FineGainAudioProcessor::createEditor()
{
    return new FineGainAudioProcessorEditor (*this);
}

//==============================================================================
void FineGainAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    
}

void FineGainAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
   
}

//==============================================================================

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FineGainAudioProcessor();
}
