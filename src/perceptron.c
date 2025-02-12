#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

// random_weights(p) sets all of the weights of p to random values 0-1
// requires: p is not null
void random_weights(perceptron *p) {
  for (int i = 0; i < p->input_amount; i++) {
    p->weights[i] = (float) rand() / RAND_MAX;
  }
}

// init_perceptron(input_amount, bias) returns a  pointer to a perceptron
//    initialized with the passed values and random weights
perceptron * init_perceptron(int input_amount, float bias) {
  perceptron *p = malloc(sizeof(perceptron));
  if (p == NULL) {
    printf("perceptron malloc failed\n");
    return NULL;
  }
  p->input_amount = input_amount;
  p->weights = malloc(input_amount * sizeof(float));
  if (p->weights == NULL) {
    printf("perceptron weights malloc failed\n");
    return NULL;
  }
  random_weights(p);
  p->bias = bias;
  return p;
}

// init_inputs(input_amount) returns a pointer to the inputs type that can hold
//    input_amount inputs
inputs *init_inputs(int input_amount) {
  inputs *in = malloc(sizeof(inputs));
  if (in == NULL) {
    printf("inputs malloc failed\n");
    return NULL;
  }
  in->input_amount = input_amount;
  in->data = malloc(input_amount * sizeof(float));
  if (in->data == NULL) {
    printf("inputs data malloc failed\n");
    return NULL;
  }
  return in;
}

// read_inputs(in) reads console input and populates the inputs data
// requires: in is not null
// effects: reads from console
void read_inputs(inputs *in) {
  float input = 0;
  for (int i = 0; i < in->input_amount; i++) {
    if (scanf("%f", &input) == 1) {
      in->data[i] = input;
    } else {
      in->data[i] = 0;
    }
  }
}

// linear(p) returns the weighted sum of the inputs and bias
// requires: p is not null
//           p->weights and in->data are same length
float linear(perceptron *p, inputs *in) {
  if (p->input_amount != in->input_amount) {
    printf("p->weights and in->data are different lengths\n");
    return -1;
  }
  float sum = 0;
  for (int i = 0; i < p->input_amount; i++) {
    sum += in->data[i] * p->weights[i];
  }
  sum += p->bias;
  return sum;
}

// print_perceptron(p) prints the perceptron to the console
// requires: p is not null
// effects: writes to the console
void print_perceptron(perceptron *p) {
  for (int i = 0; i < p->input_amount; i++) {
    printf("| %.2f ", p->weights[i]);
  }
  printf("|\n");
}

// print_inputs(in) prints the inputs to the console
// requires: in is not null
// effects: writes to the console
void print_inputs(inputs *in) {
  for (int i = 0; i < in->input_amount; i++) {
    printf("| %.2f ", in->data[i]);
  }
  printf("|\n");
}

// free_perceptron(p) frees the perceptron
void free_perceptron(perceptron *p) {
  if (p->weights != NULL) {
    free(p->weights);
  }
  if (p != NULL) {
    free(p);
  }
}

// free_inputs(in) frees the inputs
void free_inputs(inputs *in) {
  if (in->data != NULL) {
    free(in->data);
  }
  if (in != NULL) {
    free(in);
  }
}
