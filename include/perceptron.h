#ifndef PERCEPTRON
#define PERCEPTRON

typedef struct {
  int input_amount;
  float *weights;
  float bias;
} perceptron;

typedef struct {
  int input_amount;
  float *data;
} inputs;

perceptron *init_perceptron(int input_amount, float bias);
inputs *init_inputs(int input_amount);
float linear(perceptron *p, inputs *in);
void read_inputs(inputs *in);
void print_perceptron(perceptron *p);
void print_inputs(inputs *in);
void free_perceptron(perceptron *p);
void free_inputs(inputs *in);

#endif
