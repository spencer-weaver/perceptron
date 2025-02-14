#include <stdio.h>
#include "perceptron.h"
#include "optimize_learn.h"
#include "color.h"

#define EPOCHS 1000
#define LEARNING_RATE 0.1
#define TARGET_ERROR 0.0001

#define TEST_TRAIN_PERCEPTRON
//#define TEST_OPTIMIZE_LEARN

int main(void) {
  
  int input_count = 0;
  int data_count = 0;

  if (1 != scanf(" %d", &input_count)) {
    printf(ERRORC "error");
    printf(THEME ": ");
    printf(VARIABLE "input_count");
    printf(THEME " scanf failed");
  }
  if (1 != scanf(" %d", &data_count)) {
    printf(ERRORC "error");
    printf(THEME ": ");
    printf(VARIABLE "data_count");
    printf(THEME " scanf failed");
  }

  perceptron *p = init_perceptron(input_count);
  data *d = init_data(data_count, input_count);

  read_data(d);

  #ifdef TEST_TRAIN_PERCEPTRON
    fit(p, d, EPOCHS, LEARNING_RATE, TARGET_ERROR);
  #endif

  #ifdef TEST_OPTIMIZE_LEARN  
    float best = test_learn_range(p, d, EPOCHS, TARGET_ERROR);
    random_weights(p);
    fit(p, d, EPOCHS, best, TARGET_ERROR);
  #endif

  free_perceptron(p);
  free_data(d);
}
