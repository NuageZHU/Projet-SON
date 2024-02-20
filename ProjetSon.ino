#include <Audio.h>

#include "MyDsp.h"

MyDsp myDsp;
AudioInputI2S in;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioConnection patchCord0(in, 0, myDsp, 0);
AudioConnection patchCord2(myDsp, 0, out, 0);
AudioConnection patchCord3(myDsp, 0, out, 1);

void setup() {
  // put your setup code here, to run once:
  pinMode(0, INPUT);
  Serial.begin(9600);
  //delay(5000);
  AudioMemory(20);
  audioShield.enable();
  audioShield.inputSelect(AUDIO_INPUT_MIC);
  audioShield.micGain(10);  // in dB
  audioShield.volume(0.5);
  myDsp.initialize();
}

void loop() {
  int sensorValue = analogRead(A0);
  float freq = sensorValue*2 + 100;
  myDsp.setFreq(freq);
  if (digitalRead(0)) { // button is pressed
    myDsp.initialize();
  }
}