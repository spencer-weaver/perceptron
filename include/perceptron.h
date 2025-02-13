#ifndef PERCEPTRON
#define PERCEPTRON

#include <stdbool.h>

typedef struct {
  int input_amount;
  float *weights;
  float bias;
} perceptron;

typedef struct {
  int input_amount;
  float *data;
} inputs;

typedef struct {
  int data_amount;
  inputs **data;
  float *targets;
} data;

perceptron *init_perceptron(int input_amount);
inputs *init_inputs(int input_amount);
data *init_data(int data_amount, int input_amount);
float linear(perceptron *p, inputs *in);
void read_inputs(inputs *in);
void read_weights(perceptron *p);
void read_data(data *d);
float activation(float linear_sum);
float predict(perceptron *p, inputs *in);
float loss(float prediction, float target);
float train(perceptron *p, inputs *in, float learning_rate, float target);
int fit(perceptron *p, data *d, int epochs, float learning_rate, float target_error);
void print_perceptron(perceptron *p);
void print_inputs(inputs *in);
void free_perceptron(perceptron *p);
void free_inputs(inputs *in);
void free_data(data *d);

#endif
