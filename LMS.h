#ifndef LMS
#define LMS

#define FILTER_SIZE 256

class Lms {
public:
  Lms();
  float tick(float Input, float Desired, float mu);
  void initialize();
  float w[FILTER_SIZE];

private:
  float x[FILTER_SIZE];
  float c[FILTER_SIZE];
  void insertInput(float Input);
};

#endif // !LMS
