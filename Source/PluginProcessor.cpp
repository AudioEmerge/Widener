/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
StereoWidthAudioProcessor::StereoWidthAudioProcessor()
{
	width_ = 1.0f;
}


StereoWidthAudioProcessor::~StereoWidthAudioProcessor()
{
}

//==============================================================================
const String StereoWidthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int StereoWidthAudioProcessor::getNumParameters()
{
	return kNumParameters;
}

float StereoWidthAudioProcessor::getParameter(int index)
{
	switch (index)
	{
	case kWidthParam:				return width_;

	default:               return 0.0f;
	}
}


void StereoWidthAudioProcessor::setParameter(int index, float newValue)
{
	switch (index)
	{
	case kWidthParam:
		width_ = newValue;
		break;
	default:
		break;
	}

}

const String StereoWidthAudioProcessor::getParameterName(int index)
{
	switch (index)
	{
	case kWidthParam:        return "width";
	default:               break;
	}
}

const String StereoWidthAudioProcessor::getParameterText(int index)
{
	return String(getParameter(index), 2);
}

bool StereoWidthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoWidthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StereoWidthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StereoWidthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoWidthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StereoWidthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoWidthAudioProcessor::setCurrentProgram (int index)
{
}

const String StereoWidthAudioProcessor::getProgramName (int index)
{
    return {};
}

void StereoWidthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StereoWidthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void StereoWidthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StereoWidthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void StereoWidthAudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	const int totalNumInputChannels = getTotalNumInputChannels();
	const int totalNumOutputChannels = getTotalNumOutputChannels();


	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{


		float* leftChannel = buffer.getWritePointer(0);
		float* rightChannel = buffer.getWritePointer(1);


		for (int i = 0; i < buffer.getNumSamples(); ++i)
		{
			float widthVal = width_ * 0.5;
			float tmp = 1 / fmax(1 + width_, 2);
			float coef_M = 1 * tmp;
			float coef_S = width_ * tmp;

			float mid = (leftChannel[i] + rightChannel[i])*coef_M;
			float sides = (rightChannel[i] - leftChannel[i])*coef_S;

			leftChannel[i] = mid - sides;
			rightChannel[i] = mid + sides;

		}
	}
}

//==============================================================================
bool StereoWidthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* StereoWidthAudioProcessor::createEditor()
{
    return new StereoWidthAudioProcessorEditor (*this);
}

//==============================================================================
void StereoWidthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	// Create an outer XML element..
	XmlElement xml("C4DMPLUGINSETTINGS");

	// add width value
	xml.setAttribute("width", width_);

	copyXmlToBinary(xml, destData);
}

void StereoWidthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

	// This getXmlFromBinary() helper function retrieves our XML from the binary blob..
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));


	if (xmlState->hasTagName("C4DMPLUGINSETTINGS"))
	{
		// ok, now pull out our parameter..
		width_ = xmlState->getIntAttribute("width", width_);
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoWidthAudioProcessor();
}
