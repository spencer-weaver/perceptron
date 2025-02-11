#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

// random_weights(p) sets all of the weights of p to random values 0-1
// requires: p is not null
void random_weights(perceptron *p) {
  for (int i = 0; i < p->input_amount; i++) {
    p->weights[i] = rand() % 100 / 100;
  }
}

perceptron * init_perceptron(int input_amount, float bias) {
  perceptron *p = malloc(sizeof(perceptron));
  p->input_amount = input_amount;
  p->weights = malloc(input_amount * sizeof(float));
  p->bias = bias;
  return p;
}

void delete_perceptron(perceptron *p) {
  free(p->weights);
  free(p);
}
