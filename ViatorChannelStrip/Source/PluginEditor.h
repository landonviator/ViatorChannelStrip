/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ViatorChannelStripAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ViatorChannelStripAudioProcessorEditor (ViatorChannelStripAudioProcessor&);
    ~ViatorChannelStripAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::GroupComponent group1, group2, group3, group4, group5, group6;
    std::vector<juce::GroupComponent*> groups = {
        &group1, &group2, &group3, &group4, &group5, &group6
      };
    
    ViatorChannelStripAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorChannelStripAudioProcessorEditor)
};
