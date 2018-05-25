/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component,
                        public AudioIODeviceCallback,
                        public Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
                                float** outputChannelData, int numOutputChannels, int numSamples) override;
    
    void audioDeviceAboutToStart (AudioIODevice* device) override;
    
    void audioDeviceStopped() override;
    
    void audioDeviceError (const String& errorMessage) override;
    
    void timerCallback() override;

private:
    //==============================================================================
    float frequency = 0;
    float sampleRate;
    int recordSize = 2000;
    float recordedSamples[2000] = { };
    int count = 0;
    float sum;
    float sumOld;
    int i, k;
    int pdState = 0;
    int thresh = 0;
    
    CriticalSection lock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
