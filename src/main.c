#include <stdio.h>
#include "perceptron.h"

int main(void) {
  
  int input_count = 2;
  float bias = 2;

  perceptron *p = init_perceptron(input_count, bias);
  inputs *in = init_inputs(input_count);

  read_inputs(in);

  print_inputs(in);
  print_perceptron(p);
  
  float sum = linear(p, in);

  printf("sum: %.2f\n", sum);

  free_perceptron(p);
  free_inputs(in);
}
