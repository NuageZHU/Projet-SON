#ifndef LMS
#define LMS

class Lms {
public:
  Lms();
  float tick(float Input, float Desired, float mu);

private:
  float w[2];
  // float x[2];
};

#endif // !LMS
