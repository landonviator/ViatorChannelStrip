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
    groups.reserve(6);
    groupTexts.reserve(6);
    
    for (int i = 0; i < groups.size(); i++) {
        addAndMakeVisible(groups[i]);
        groups[i]->setColour(0x1005400, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25f));
        groups[i]->setColour(0x1005410, juce::Colour::fromFloatRGBA(1, 1, 1, 0.25f));
        groups[i]->setText(groupTexts[i]);
    }
    
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
}
