#include "LMS.h"

Lms::Lms() {
  float w[FILTER_SIZE] = {0.0};
  float x[FILTER_SIZE] = {0.0};
  float c[FILTER_SIZE] = {0.0};
}

void Lms::initialize() {
  for (int i = 0; i < FILTER_SIZE / 3; i++) {
    c[i] = 0.5;
    w[i] = 0;
  }
  for (int i = FILTER_SIZE / 3; i < 2 * (FILTER_SIZE / 3); i++) {
    c[i] = 0.3;
    w[i] = 0;
  }
  for (int i = 2 * (FILTER_SIZE / 3); i < FILTER_SIZE; i++) {
    c[i] = 0.1;
    w[i] = 0;
  }
}

float Lms::tick(float Input, float Desired, float mu) {
  insertInput(Input);
  float y = 0.0;
  // float dFIR = 0.0;
  for (int i = 0; i < FILTER_SIZE; i++) {
    // dFIR = c[i] * x[i];
    y += w[i] * x[i];
  }
  float error = Desired - y;
  for (int i = 0; i < FILTER_SIZE; i++) {
    w[i] = w[i] + mu * error * x[i]; /// (normBarray + 0.0001f);
  }
  return error;
}

// float Lms::tick(float Input, float Desired, float mu) {
//   insertInput(Input);
//   float output = 0.0;
//   for (int i = 0; i < FILTER_SIZE; i++) {
//     output += w[i] * x[i];
//   }
//   float error = Desired - output;
//   for (int i = 0; i < FILTER_SIZE; i++) {
//     w[i] = w[i] + mu * error * x[i];
//   }
//   return error;
// }
void Lms::insertInput(float Input) {
  for (int i = FILTER_SIZE - 1; i > 0; i--) {
    x[i] = x[i - 1];
  }
  x[0] = Input;
}
