#include "LMS.h"
#define PI 3.141592653589
#define FILTER_SIZE 2

Lms::Lms() {
  float w[FILTER_SIZE] = {0.0};
  // float x[FILTER_SIZE] = {0.0};
}

float Lms::tick(float Input, float Desired, float mu) {
  float output = 0.0;
  for (int i = 0; i < FILTER_SIZE; i++) {
    output += w[i] * Input;
  }
  float error = Desired - output;
  for (int i = 0; i < FILTER_SIZE; i++) {
    w[i] = w[i] + mu * error * Input;
  }
  return output;
}
