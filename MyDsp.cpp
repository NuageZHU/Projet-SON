
#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767
#define DIV_16 0.0000305185

#define PI 3.141592653589

float freq = 440;
float tau = 0.1;

MyDsp::MyDsp()
    : AudioStream(AUDIO_OUTPUTS, new audio_block_t *[AUDIO_OUTPUTS]), lms(),
      sine(AUDIO_SAMPLE_RATE_EXACT),
      noise() {
  // setting up DSP objects
  freq = 440;
  tau = 0.1;
  bool lmsCheck = false;
}

MyDsp::~MyDsp() {}

void MyDsp::setFreq(float value) { freq = value; }

void MyDsp::update(void) {
  sine.setFrequency(freq);
  audio_block_t *inBlock[AUDIO_OUTPUTS];
  audio_block_t *outBlock[AUDIO_OUTPUTS];
  for (int channel = 0; channel < AUDIO_OUTPUTS; channel++) {
    inBlock[channel] = receiveReadOnly(channel);
    outBlock[channel] = allocate();
    if (outBlock[channel]) {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        float currentSample = 0;
        float currentNoise = noise.tick()*0.5;
        float currentSine = sine.tick()*0.5;
        if (inBlock[channel]) {
          currentSample = inBlock[channel]->data[i] * DIV_16;
        }
        if (lmsCheck) {
          currentSample = lms.tick(currentNoise, currentSample + currentNoise + currentSine, 0.001);
        }
        else {
          currentSample = currentSample + currentNoise + currentSine;
        }
        //currentSample = lms.tick(currentNoise, currentSample + currentNoise, 0.1);
        currentSample = max(-1, min(1, currentSample));
        int16_t val = currentSample * MULT_16;
        outBlock[channel]->data[i] = val;
      }
      transmit(outBlock[channel], channel);
      if (inBlock[channel])
        release(inBlock[channel]);
      release(outBlock[channel]);
    }
  }
}

