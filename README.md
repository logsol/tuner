# Tuner
A simple standalone app for macOS based on JUCE that detects the frequency of an instrument and shows its note based on autocorrelation.

<img alt="Screenshot of application" src="https://user-images.githubusercontent.com/692826/40535041-3dab748c-6008-11e8-8d93-6c73fa36d9fd.png">

[Download now](https://github.com/logsol/tuner/releases/download/1.0.0/Tuner.app.zip)

# Additional research

## Different Approaches of Pitch Detection
- Using FFT 
  - This introduces a tradeoff between pitch detection resolution and data acquisition time (or sample rate). See [paper on guitar tuner based on FFT](https://arxiv.org/pdf/0912.0745.pdf)
  - “FFT is actually not a great way of making a tuner. FFT has inherently a finite frequency resolution and it's not easy to detect very small frequency changes without making the time window extremely long which makes it unwieldy and sluggish.” [dsp stack exchange](https://dsp.stackexchange.com/questions/1317/is-there-an-algorithm-for-finding-a-frequency-without-dft-or-fft?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa)
- Auto Correlation
  - Has the advantage of being fast in pitch detection and detects small changes in frequency
- YIN
  - It is based on the well-known autocorrelation method with a number of modifications that combine to prevent errors. The algorithm has several desirable features. Error rates are about three times lower than the best competing methods. There is no upper limit on the frequency search range, so the algorithm is suited for high-pitched voices and music. The algorithm is relatively simple and may be implemented efficiently and with low latency, and it involves few parameters that must be tuned. [see paper](http://audition.ens.fr/adc/pdf/2002_JASA_YIN.pdf)
- Zero Crossing Detection
  - Some of the simplest guitar tuners just used low-pass or band-pass filtering and measured the time between zero-crossings.  The reciprocal gives a frequency estimate. [dsp stack exchange](https://dsp.stackexchange.com/questions/1317/is-there-an-algorithm-for-finding-a-frequency-without-dft-or-fft?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa)
- Dynamic Wavelet
- Phase Locked Loop
- Delay Locked Loop

## Octave jumping problem
We hear stuff with our ears and brain (and as such we hear a "pitch" of a tone that is most often associated with the fundamental frequency f0) but the Pitch Detection Algorithm (PDA) is not hearing anything but is doing math and making logical decision that it is programmed to do. so, mathematically, if a tone is judged to be periodic with fundamental frequency of 440 Hz, it is just as well a tone of 220 Hz or 146.67 Hz or 110 Hz or 88 Hz or 55 Hz. it is actually just as periodic with those fundamentals (and the periods associated with those fundamentals) as it is at 440 Hz.

### Possible Solutions
- Make the pitch you select at earlier times be a little "sticky" and preferred, so that when there is suddenly a single frame that concludes that another candidate an octave high or low is the pitch, you can stick with the pitch you already have chosen for earlier frames
- Disregard octaves like most guitar tuners
- See [octave error immune pitch detection](https://www.tandfonline.com/doi/abs/10.1080/09298210500235301?journalCode=nnmr20)

## Discarding Outliers
- Averaging
- Calculation standard deviation and ignoring values outside of the normal range of values varying from each other

## Other ways to improve this tuner
- Preprocessing by filtering (e.g. band pass filter - hamming window)
- Using a ring buffer
- Optimising rendering interval time
