#include "LMS.h"
#define FILTER_SIZE 1

Lms::Lms() { float w[FILTER_SIZE] = {0.0}; }

float Lms::tick(float Input, float Desired, float mu) {
  float output = 0.0;
  for (int i = 0; i < FILTER_SIZE; i++) {
    output += w[i] * Input;
  }
  float error = Desired - output;
  for (int i = 0; i < FILTER_SIZE; i++) {
    w[i] = w[i] + mu * error * Input;
  }
  return error;
}
