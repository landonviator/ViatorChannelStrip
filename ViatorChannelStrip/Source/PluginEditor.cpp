/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ViatorChannelStripAudioProcessorEditor::ViatorChannelStripAudioProcessorEditor (ViatorChannelStripAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    shadowProperties.radius = 15;
    shadowProperties.offset = juce::Point<int> (-2, 6);
    dialShadow.setShadowProperties (shadowProperties);
    
    groups.reserve(6);
    groupTexts.reserve(6);
    
    for (int i = 0; i < groups.size(); i++) {
        addAndMakeVisible(groups[i]);
        groups[i]->setColour(0x1005400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25f));
        groups[i]->setColour(0x1005410, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25f));
        groups[i]->setText(groupTexts[i]);
    }
    
    //Saturation model chooser
    addAndMakeVisible(saturationModelSlider);
    saturationModelSlider.setRange(0, 4, 1);
    saturationModelSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    saturationModelSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
    saturationModelSlider.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    saturationModelSlider.setColour(0x1001700, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    saturationModelSlider.setColour(0x1001500, juce::Colour::fromFloatRGBA(0, 0, 0, 0.0f));
    saturationModelSlider.setLookAndFeel(&customDial);
    saturationModelSlider.setComponentEffect(&dialShadow);
    
    //Drive slider
    addAndMakeVisible(driveSlider);
    driveSlider.setRange(0, 24, 0.5f);
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 64, 32);
    driveSlider.setColour(0x1001400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    driveSlider.setColour(0x1001700, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    driveSlider.setColour(0x1001500, juce::Colour::fromFloatRGBA(0, 0, 0, 0.0f));
    driveSlider.setLookAndFeel(&customDial);
    driveSlider.setComponentEffect(&dialShadow);
    
    //Drive label
    addAndMakeVisible(driveLabel);
    driveLabel.setText("Drive", juce::dontSendNotification);
    driveLabel.setJustificationType(juce::Justification::centred);
    driveLabel.attachToComponent(&driveSlider, false);
    
    //Making the window resizable by aspect ratio and setting size
    AudioProcessorEditor::setResizable(true, true);
    AudioProcessorEditor::setResizeLimits(682, 341, 1536, 768);
    AudioProcessorEditor::getConstrainer()->setFixedAspectRatio(2.0);
    setSize (1024, 512);
}

ViatorChannelStripAudioProcessorEditor::~ViatorChannelStripAudioProcessorEditor()
{
}

//==============================================================================
void ViatorChannelStripAudioProcessorEditor::paint (juce::Graphics& g)
{
    juce::Rectangle<int> background = AudioProcessorEditor::getLocalBounds();
    g.setGradientFill(juce::ColourGradient::vertical(juce::Colour::fromFloatRGBA(0.18f, 0.20f, 0.24f, 1.0), AudioProcessorEditor::getHeight() * .01, juce::Colour::fromFloatRGBA(0.11f, 0.13f, 0.17f, 1.0), AudioProcessorEditor::getHeight() * .99));
    g.fillRect(background);
}

void ViatorChannelStripAudioProcessorEditor::resized()
{
    //Master bounds object
    juce::Rectangle<int> bounds = AudioProcessorEditor::getLocalBounds();
    
    //Quadrant One
    juce::Rectangle<int> square1;
    square1.setBounds(0, 0, bounds.getWidth() / 3, bounds.getHeight() / 2);
    group1.setBounds(square1.getX(), square1.getY(), square1.getWidth(), square1.getHeight());
    
    //Quadrant Two
    juce::Rectangle<int> square2;
    square2.setBounds(square1.getX(), square1.getY() + square1.getHeight(), square1.getWidth(), square1.getHeight());
    group2.setBounds(square2.getX(), square2.getY(), square2.getWidth(), square2.getHeight());
    
    //Quadrant Three
    juce::Rectangle<int> square3;
    square3.setBounds(square1.getX() + square1.getWidth(), square1.getY(), square2.getWidth(), square2.getHeight());
    group3.setBounds(square3.getX(), square3.getY(), square3.getWidth(), square3.getHeight());
    
    //Quadrant Four
    juce::Rectangle<int> square4;
    square4.setBounds(square3.getX(), square3.getY() + square3.getHeight(), square3.getWidth(), square3.getHeight());
    group4.setBounds(square4.getX(), square4.getY(), square4.getWidth(), square4.getHeight());
    
    //Quadrant Five
    juce::Rectangle<int> square5;
    square5.setBounds(square3.getX() + square3.getWidth(), square3.getY(), square4.getWidth(), square4.getHeight());
    group5.setBounds(square5.getX(), square5.getY(), square5.getWidth(), square5.getHeight());
    
    //Quadrant Six
    juce::Rectangle<int> square6;
    square6.setBounds(square5.getX(), square5.getY() + square5.getHeight(), square5.getWidth(), square5.getHeight());
    group6.setBounds(square6.getX(), square6.getY(), square6.getWidth(), square6.getHeight());
    
    /*=========================================================================================================================================*/
    
    //Saturation flex box
    juce::FlexBox saturationFlexBox;
    saturationFlexBox.flexDirection = juce::FlexBox::Direction::row;
    saturationFlexBox.flexWrap = juce::FlexBox::Wrap::noWrap;
    saturationFlexBox.alignContent = juce::FlexBox::AlignContent::center;
            
    juce::Array<juce::FlexItem> saturationItemArray;
    saturationItemArray.add(juce::FlexItem(square1.getWidth() * 0.65f, square1.getHeight() * 0.65f, saturationModelSlider).withMargin(juce::FlexItem::Margin(0, 0, 0, 0)));
    saturationItemArray.add(juce::FlexItem(square1.getWidth() * 0.65f, square1.getHeight() * 0.65f, driveSlider).withMargin(juce::FlexItem::Margin(0, 0, 0, square1.getWidth() * -0.2)));
            
    saturationFlexBox.items = saturationItemArray;
    saturationFlexBox.performLayout(square1.removeFromLeft(square1.getWidth()));
    
    if (AudioProcessorEditor::getWidth() < 830){
        driveLabel.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.0f));
    } else {
        driveLabel.setColour(0x1000281, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25f));
    }
}
