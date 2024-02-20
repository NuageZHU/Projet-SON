
#include "MyDsp.h"

#define AUDIO_OUTPUTS 1

#define MULT_16 32767
#define DIV_16 0.0000305185

#define PI 3.141592653589

float freq = 440;

MyDsp::MyDsp()
  : AudioStream(AUDIO_OUTPUTS, new audio_block_t *[AUDIO_OUTPUTS]), 
    lms(), 
    //project(),
    sine(AUDIO_SAMPLE_RATE_EXACT),
    noise() {
  // setting up DSP objects
  freq = 440;
  bool lmsCheck = false;
}

MyDsp::~MyDsp() {}

void MyDsp::setFreq(float value) {
  freq = value;
}

void MyDsp::initialize() {
  lms.initialize();
}

void MyDsp::update(void) {
  sine.setFrequency(freq);
  audio_block_t *inBlock[AUDIO_OUTPUTS];
  audio_block_t *outBlock[AUDIO_OUTPUTS];
  inBlock[0] = receiveReadOnly(0);
  outBlock[0] = allocate();
  if (outBlock[0]) {
    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
      float currentSample = 0;
      float currentNoise = noise.tick()*0.5;
      if (inBlock[0]) {
        currentSample = inBlock[0]->data[i] * DIV_16;
      }
      float e = lms.tick(currentNoise, currentSample, 0.01);
      //currentSample = currentSample + currentNoise;
      //float e = project.tick(currentNoise, currentSample) * 100;

      //currentSample = lms.tick(currentNoise, currentSample + currentNoise, 0.1);
      currentNoise = max(-1, min(1, currentNoise));
      Serial.println(e);

      //e = max(-1,min(1, e));

      int16_t val = currentNoise * MULT_16;
      outBlock[0]->data[i] = val;

    }
    transmit(outBlock[0], 0);
    if (inBlock[0]) {
      release(inBlock[0]);
    }
    release(outBlock[0]);
  }
}
