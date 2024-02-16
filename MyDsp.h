#ifndef faust_teensy_h_
#define faust_teensy_h_

#include "Arduino.h"
#include "AudioStream.h"
#include "Audio.h"

#include "LMS.h"
#include "Noise.h"
#include "Sine.h"

class MyDsp : public AudioStream
{
  public:
    MyDsp();
    ~MyDsp();
    
    virtual void update(void);
    void setFreq(float value);
    void updateLmsCheck();
    bool lmsCheck;
    
  private:
    Lms lms;
    Sine sine;
    Noise noise;
    
};


#endif
