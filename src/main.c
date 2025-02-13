#include <stdio.h>
#include "perceptron.h"

int main(void) {

  float learning_rate = 0.1;
  int epochs = 1000;
  
  int input_count = 0;
  int data_count = 0;

  scanf(" %d", &input_count);
  scanf(" %d", &data_count);

  perceptron *p = init_perceptron(input_count);
  data *d = init_data(data_count, input_count);

  p->bias = 0;

  read_data(d);

  fit(p, d, epochs, learning_rate, 0.001);

  free_perceptron(p);
  free_data(d);
}
