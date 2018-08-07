/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
StereoWidthAudioProcessorEditor::StereoWidthAudioProcessorEditor (StereoWidthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	//GroupComponent
	addAndMakeVisible(mainGroup_);
	mainGroup_.setText("Stereo Widening");
	mainGroup_.setColour(GroupComponent::outlineColourId, Colours::white);

	//Slider
	addAndMakeVisible(widthSlider_);
	widthSlider_.setRange(0.0, 2.0, 0.1);
	widthSlider_.setValue(0.0);
	widthSlider_.setSliderStyle(Slider::Rotary);
	widthSlider_.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
	widthSlider_.setPopupDisplayEnabled(true, false, this);
	widthSlider_.addListener(this);

	//Labels
	addAndMakeVisible(narrowLabel_ = new Label("new label",
		TRANS("Narrow")));
	narrowLabel_->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	narrowLabel_->setJustificationType(Justification::centred);
	narrowLabel_->setEditable(false, false, false);
	narrowLabel_->setColour(TextEditor::textColourId, Colours::black);
	narrowLabel_->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(normalLabel_ = new Label("new label",
		TRANS("Normal")));
	normalLabel_->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	normalLabel_->setJustificationType(Justification::centred);
	normalLabel_->setEditable(false, false, false);
	normalLabel_->setColour(TextEditor::textColourId, Colours::black);
	normalLabel_->setColour(TextEditor::backgroundColourId, Colour(0x00000000));

	addAndMakeVisible(wideLabel_ = new Label("new label",
		TRANS("Wide")));
	wideLabel_->setFont(Font(15.00f, Font::plain).withTypefaceStyle("Regular"));
	wideLabel_->setJustificationType(Justification::centred);
	wideLabel_->setEditable(false, false, false);
	wideLabel_->setColour(TextEditor::textColourId, Colours::black);
	wideLabel_->setColour(TextEditor::backgroundColourId, Colour(0x00000000));


	//Set Look & feel

	widthSlider_.setLookAndFeel(&widthKnobLookAndFeel);
	
    setSize (320, 240);

	startTimer(50);
}

StereoWidthAudioProcessorEditor::~StereoWidthAudioProcessorEditor()
{
	narrowLabel_ = nullptr;
	normalLabel_ = nullptr;
	wideLabel_ = nullptr;
}

//==============================================================================
void StereoWidthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void StereoWidthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	mainGroup_.setBounds(2, 2, 316, 236);

	widthSlider_.setBounds(70, 50, 180, 180);

	narrowLabel_->setBounds(10, 200, 150, 24);
	normalLabel_->setBounds(90, 28, 150, 24);
	wideLabel_->setBounds(160, 200, 150, 24);

}

void StereoWidthAudioProcessorEditor::timerCallback()
{


	widthSlider_.setValue(processor.width_, dontSendNotification);
	

}

void StereoWidthAudioProcessorEditor::sliderValueChanged(Slider* sliderThatWasMoved)
{


	if (sliderThatWasMoved == &widthSlider_)
	{
		processor.setParameterNotifyingHost(StereoWidthAudioProcessor::Parameters::kWidthParam,
			(float)widthSlider_.getValue());
	}
}