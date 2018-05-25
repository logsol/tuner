/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (600, 400);
    startTimer (50);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setFont (Font (146.0f));
    g.setColour (Colours::orange);
    
    float note = round(log(frequency / 440.0) / log(2) * 12 + 69);
    juce::String noteName = MidiMessage::getMidiNoteName(note, true, false, 3);
    
    //if (noteName == "E") {
        g.drawText (noteName, getLocalBounds(), Justification::centred, true);
    //}
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::audioDeviceIOCallback (const float** inputChannelData, int numInputChannels,
                            float** outputChannelData, int numOutputChannels, int numSamples)
{
    const ScopedLock sl (lock);
    
    // Todo: Could be slightly improved by recording into a ring buffer
    // Todo: Play around with threshold to find a value for good detection
    
    for (int l = 0; l < numSamples; ++l) {
        
        if (count < recordSize) {
            
            // Record 2000 samples (only use left / first channel)
            recordedSamples[count] = inputChannelData[0][l];
            count++;
            
        } else {
            
            // After samples are recorded
            sum = 0;
            pdState = 0;
            int period = 0;
            
            for (i=0; i < recordSize; i++) {
                
                // Autocorrelation
                sumOld = sum;
                sum = 0;
                
                for (k=0; k < recordSize-i; k++) {
                    sum += recordedSamples[k] * recordedSamples[k+i];
                }
                
                // Peak Detect State Machine
                if (pdState == 2 && (sum-sumOld) <= 0) {
                    period = i;
                    pdState = 3;
                }
                
                if (pdState == 1 && (sum > thresh) && (sum-sumOld) > 0) {
                    pdState = 2;
                }
                
                if (!i) {
                    thresh = sum * 0.5;
                    pdState = 1;
                }
            }

            // Frequency identified in Hz
            if (thresh > 10) {
                frequency = sampleRate / period;
            }
            count = 0;
            
        }
    }
}

void MainComponent::audioDeviceAboutToStart (AudioIODevice* device)
{
    sampleRate = device->getCurrentSampleRate();
}

void MainComponent::audioDeviceStopped()
{
    
}

void MainComponent::audioDeviceError (const String& errorMessage)
{
    std::cout << errorMessage;
}

void MainComponent::timerCallback()
{
    repaint();
}
