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
    
    std::string groupOneText = "Saturation";
    std::string groupTwoText = "Surgery";
    std::string groupThreeText = "VCA";
    std::string groupFourText = "Color";
    std::string groupFiveText = "Something";
    std::string groupSixText = "Limiter";
    
    std::vector<std::string> groupTexts = {
        groupOneText, groupTwoText, groupThreeText, groupFourText, groupFiveText, groupSixText
    };
    
    ViatorChannelStripAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorChannelStripAudioProcessorEditor)
};
