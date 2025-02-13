#define OUTPUT

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "perceptron.h"

// random_weights(p) sets all of the weights of p to random values 0-1
// requires: p is not null
void random_weights(perceptron *p) {
  for (int i = 0; i < p->input_amount; i++) {
    #ifdef OUTPUT
    printf("setting weight[%d]: ", i);
    #endif
    p->weights[i] = (float) rand() / RAND_MAX;
    #ifdef OUTPUT
    printf("%.5f\n", p->weights[i]);
    #endif
  }
  p->bias = (float) rand() / RAND_MAX;
}

// init_perceptron(input_amount, bias) returns a  pointer to a perceptron
//    initialized with the passed values and random weights and bias
perceptron *init_perceptron(int input_amount) {
  perceptron *p = malloc(sizeof(perceptron));
  if (p == NULL) {
    printf("perceptron malloc failed\n");
    free(p);
    return NULL;
  }
  p->input_amount = input_amount;
  p->weights = malloc(input_amount * sizeof(float));
  if (p->weights == NULL) {
    printf("perceptron weights malloc failed\n");
    free(p->weights);
    free(p);
    return NULL;
  }
  random_weights(p);
  return p;
}

// init_inputs(input_amount) returns a pointer to the inputs type that can hold
//    input_amount inputs
inputs *init_inputs(int input_amount) {
  inputs *in = malloc(sizeof(inputs));
  if (in == NULL) {
    printf("inputs malloc failed\n");
    free(in);
    return NULL;
  }
  in->input_amount = input_amount;
  in->data = malloc(input_amount * sizeof(float));
  if (in->data == NULL) {
    printf("inputs data malloc failed\n");
    free(in->data);
    free(in);
    return NULL;
  }
  return in;
}

// init_data(data_amount) returns a pointer to a data structure
data *init_data(int data_amount, int input_amount) {
  data *d = malloc(data_amount * sizeof(data));
  if (d == NULL) {
    printf("data malloc failed\n");
    free(d);
    return NULL;
  } else {
    d->data_amount = data_amount;
  }
  d->data = malloc(data_amount * sizeof(inputs *));
  if (d->data == NULL) {
    printf("data data malloc failed\n");
    free(d->data);
    free(d);
    return NULL;
  }
  for (int i = 0; i < data_amount; i++) {
    d->data[i] = init_inputs(input_amount);
  }
  d->targets = malloc(data_amount * sizeof(float));
  if (d->targets == NULL) {
    printf("data targets malloc failed\n");
    free(d->targets);
    free(d->data);
    free(d);
    return NULL;
  }
  return d;
}

// read_weights(p) reads console input and populates the perceptrons weights
//    for use when manually assigning weights
// requires: p is not null
// effects: reads from console
void read_weights(perceptron *p) {
  float input = 0;
  for (int i = 0; i < p->input_amount; i++) {
    if (scanf("%f", &input) == 1) {
      p->weights[i] = input;
    } else {
      p->weights[i] = 0;
    }
  }
}

// read_inputs(in) reads console input and populates the inputs data
// requires: in is not null
// effects: reads from console
void read_inputs(inputs *in) {
  float input = 0;
  for (int i = 0; i < in->input_amount; i++) {
    if (scanf(" %f", &input) == 1) {
      #ifdef OUTPUT
      printf("setting input[%d]: %.5f\n", i, input);
      #endif
      in->data[i] = input;
    } else {
      in->data[i] = 0;
    }
  }
}

// read_data(d) reads console input and populates the data values
// requires: d is not null
// effects: reads from console
void read_data(data *d) {
  float input = 0;
  for (int i = 0; i < d->data_amount; i++) {
    #ifdef OUTPUT
    printf("setting data[%d]\n", i);
    #endif
    read_inputs(d->data[i]);
  }
  for (int i = 0; i < d->data_amount; i++) {
    if (scanf(" %f", &input) == 1) {
      d->targets[i] = input;
      #ifdef OUTPUT
      printf("setting data->target[%d]: %.5f\n", i, input);
      #endif
    } else {
      d->targets[i] = 0;
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

// activation(linear_sum, threshold) returns true if activated
float activation(float linear_sum) {
  return linear_sum > 0 ? linear_sum : 0;
}

// predict(p, in) returns the prediction made from inputs in
// requires: p and in are not null
float predict(perceptron *p, inputs *in) {
  float linear_sum = linear(p, in);
  return activation(linear_sum);
}

// loss(prediction, target) returns the error in the prediction
float loss(float prediction, float target) {
  return target - prediction;
}

// train(p, in, target) adjusts the weights of p, returns error
// requires: p and in are not null
float train(perceptron *p, inputs *in, float learning_rate, float target) {
  float prediction = predict(p, in);
  float error = loss(prediction, target);
  #ifdef OUTPUT
  printf("inputs:\n");
  print_inputs(in);
  printf("target: %.5f\n", target);
  printf("prediction: %.5f\nerror: %.5f\n", prediction, error);
  #endif
  for (int i = 0; i < p->input_amount; i++) {
    #ifdef OUTPUT
    printf("updating weight[%d]: %.5f -> %.5f\n", i, p->weights[i], p->weights[i] + learning_rate * error * in->data[i]);
    #endif
    p->weights[i] += learning_rate * error * in->data[i];
  }
  #ifdef OUTPUT
  printf("updating bias: %.5f -> %.5f\n", p->bias, p->bias + learning_rate * error);
  #endif
  p->bias += learning_rate * error;
  return error;
}

// fit(p, d, epochs) trains p to fit data d over epochs iterations. returns the
//    last epoch needed before reaching target error or epochs
// requires: p, d are not null
void fit(perceptron *p, data *d, int epochs, float learning_rate, float target_error) {
  float error = 0;
  for (int i = 0; i < epochs; i++) {
    #ifdef OUTPUT
    printf("epoch: %d\n", i + 1);
    #endif
    for (int j = 0; j < d->data_amount; j++) {
      error += fabs(train(p, d->data[j], learning_rate, d->targets[j]));
    }
    if (error < target_error) {
      printf("target error reached on epoch %d: %.5f\n", i, error);
      return;
    }
    error = 0;
  }
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

// free_data(d) frees the data
void free_data(data *d) {
  if (d->targets != NULL) {
    free(d->targets);
  }
  if (d->data != NULL) {
    for (int i = 0; i < d->data_amount; i++) {
      free(d->data[i]);
    }
    free(d->data);
  }
  if (d != NULL) {
    free(d);
  }
}
