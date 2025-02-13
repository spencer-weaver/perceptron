
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "perceptron.h"
#include "print_settings.h"
#include "color.h"

// range definitions
#define CLOSE 0.0001

// random_weights(p) sets all of the weights of p to random values 0-1
// requires: p is not null
void random_weights(perceptron *p) {
  #ifdef PRETTY_TRAIN
    printf(THEME "initializing ");
    printf(VARIABLE "perceptron");
    printf(THEME ":\n");
  #endif
  for (int i = 0; i < p->input_amount; i++) {
    #ifdef PRETTY_TRAIN
      printf(THEME "  initializing ");
      printf(VARIABLE "weight");
      printf(THEME "[");
      printf(VARIABLE "%d", i);
      printf(THEME "]");
      printf(THEME ": ");
    #endif
    p->weights[i] = (float) rand() / RAND_MAX;
    #ifdef PRETTY_TRAIN
      if (p->weights[i] < 0) {
        printf(INPUT "%.7f", p->weights[i]);
      } else {
        printf(INPUT " %.7f", p->weights[i]);
      }
      printf(THEME "\n");
    #endif
  }
  p->bias = (float) rand() / RAND_MAX;
}

// init_perceptron(input_amount, bias) returns a  pointer to a perceptron
//    initialized with the passed values and random weights and bias
perceptron *init_perceptron(int input_amount) {
  perceptron *p = malloc(sizeof(perceptron));
  if (p == NULL) {
    printf(ERRORC "error");
    printf(THEME ": ");
    printf(VARIABLE "perceptron");
    printf(THEME " malloc failed\n");
    free(p);
    return NULL;
  }
  p->input_amount = input_amount;
  p->weights = malloc(input_amount * sizeof(float));
  if (p->weights == NULL) {
    printf(ERRORC "error");
    printf(THEME ": ");
    printf(VARIABLE "perceptron");
    printf(THEME "->");
    printf(VARIABLE "weights");
    printf(THEME " malloc failed\n");
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
    printf(ERRORC "error");
    printf(THEME ": ");
    printf(VARIABLE "inputs");
    printf(THEME " malloc failed\n");
    free(in);
    return NULL;
  }
  in->input_amount = input_amount;
  in->data = malloc(input_amount * sizeof(float));
  if (in->data == NULL) {
    printf(ERRORC "error");
    printf(THEME ": ");
    printf(VARIABLE "inputs");
    printf(THEME "->");
    printf(VARIABLE "data");
    printf(THEME " malloc failed\n");
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
    printf(ERRORC "error");
    printf(THEME ": ");
    printf(VARIABLE "data");
    printf(THEME " malloc failed\n");
    free(d);
    return NULL;
  } else {
    d->data_amount = data_amount;
  }
  d->data = malloc(data_amount * sizeof(inputs *));
  if (d->data == NULL) {
    printf(ERRORC "error");
    printf(THEME ": ");
    printf(VARIABLE "data");
    printf(THEME "->");
    printf(VARIABLE "data");
    printf(THEME " malloc failed\n");
    free(d->data);
    free(d);
    return NULL;
  }
  for (int i = 0; i < data_amount; i++) {
    d->data[i] = init_inputs(input_amount);
  }
  d->targets = malloc(data_amount * sizeof(float));
  if (d->targets == NULL) {
    printf(ERRORC "error");
    printf(THEME ": ");
    printf(VARIABLE "data");
    printf(THEME "->");
    printf(VARIABLE "targets");
    printf(THEME " malloc failed\n");
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
      #ifdef PRETTY_TRAIN
        printf("  setting ");
        printf(VARIABLE "input");
        printf(THEME "[");
        printf(INPUT "%d", i);
        printf(THEME "]:");
        printf(INPUT " %.7f", input);
        printf(THEME "\n");
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
    #ifdef PRETTY_TRAIN
      printf("setting ");
      printf(VARIABLE "data");
      printf(THEME "[");
      printf(INPUT "%d", i);
      printf(THEME "]:\n");
    #endif
    read_inputs(d->data[i]);
  }
  for (int i = 0; i < d->data_amount; i++) {
    if (scanf(" %f", &input) == 1) {
      d->targets[i] = input;
      #ifdef PRETTY_TRAIN
        printf("setting ");
        printf(VARIABLE "target");
        printf(THEME "[");
        printf(INPUT "%d", i);
        printf(THEME "]: ");
        if (input < 0) {
          printf(INPUT "%.7f", input);
        } else {
          printf(INPUT " %.7f", input);
        }
        printf(THEME "\n");
      #endif
    } else {
      d->targets[i] = 0;
    }
  }
  #if defined(PRETTY_TRAIN) || defined(PRETTY)
    printf("\n");
  #endif
}

// linear(p) returns the weighted sum of the inputs and bias
// requires: p is not null
//           p->weights and in->data are same length
float linear(perceptron *p, inputs *in) {
  if (p->input_amount != in->input_amount) {
    printf(ERRORC "error");
    printf(THEME ": ");
    printf(VARIABLE "p");
    printf(THEME "->");
    printf(VARIABLE "weights");
    printf(THEME " and ");
    printf(VARIABLE "in");
    printf(THEME "->");
    printf(VARIABLE "data");
    printf(THEME " are different lengths\n");
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
  #ifdef PRETTY_TRAIN
    print_inputs(in);
    print_perceptron(p);
    float neg = target;
    if (neg < 0) {
      printf(THEME "\n      target:     %.7f", neg);
    } else {
      printf(THEME "\n      target:      %.7f", neg);
    }
    printf(THEME "\n");
    neg = prediction;
    if (neg < 0) {
      printf(THEME "      prediction: %.7f", neg);
    } else {
      printf(THEME "      prediction:  %.7f", neg);
    }
    printf(THEME "\n");
    printf(THEME "      error:      ");
    neg = target - prediction;
    if (neg < 0) {
      if (neg < CLOSE) {
        printf(CLOSEC "%.7f", neg);
      } else {
        printf(FARC "%.7f", neg);
      }
    } else {
      if (neg < CLOSE) {
        printf(CLOSEC " %.7f", neg);
      } else {
        printf(FARC " %.7f", neg);
      }
    }
    printf(THEME "\n\n");
  #endif
  for (int i = 0; i < p->input_amount; i++) {
    #ifdef PRETTY_TRAIN
      printf(THEME "    updating ");
      printf(VARIABLE "weight");
      printf(THEME "[");
      printf(GREEN "%d", i);
      printf(THEME "]: ");
      neg = p->weights[i];
      if (neg < 0) {
        printf(RED "%.7f", neg);
      } else {
        printf(RED " %.7f", neg);
      }
      printf(THEME " -> ");
      neg = p->weights[i] + learning_rate * error * in->data[i];
      if (neg < 0) {
        printf(GREEN "%.7f", neg);
      } else {
        printf(GREEN " %.7f", neg);
      }
      printf(THEME " \n");
    #endif
    p->weights[i] += learning_rate * error * in->data[i];
  }
  #ifdef PRETTY_TRAIN
    printf(THEME "    updating ");
    printf(VARIABLE "bias");
    printf(THEME ":     ");
    neg = p->bias + learning_rate * error;
    if (neg < 0) {
      printf(RED " %.7f", neg);
    } else {
      printf(RED "  %.7f", neg);
    }
    printf(THEME " -> ");
    neg = p->bias + learning_rate * error;
    if (neg < 0) {
      printf(GREEN "%.7f", neg);
    } else {
      printf(GREEN " %.7f", neg);
    }
    printf(THEME " \n");
    printf("\n");
  #endif
  p->bias += learning_rate * error;
  return error;
}

// fit(p, d, epochs) trains p to fit data d over epochs iterations. returns the
//    last epoch needed before reaching target error or epochs
// requires: p, d are not null
int fit(perceptron *p, data *d, int epochs, float learning_rate, float target_error) {
  float error = 0;
  for (int i = 0; i < epochs; i++) {
    error = 0;
    #ifdef PRETTY_TRAIN
      printf(THEME "\n_______________________\n");
      printf(THEME "                        \\\n");
      printf(EPOCHC "                   epoch");
      printf(THEME ": ");
      printf(EPOCHC "%d\n", i + 1);
      printf(THEME "                       /\n");
      printf(THEME "^^^^^^^^^^^^^^^^^^^^^^^\n");
    #endif
    for (int j = 0; j < d->data_amount; j++) {
      #ifdef PRETTY_TRAIN
        printf(THEME "\n____________\n");
        printf(THEME "        test");
        printf(THEME ": ");
        printf(EPOCHC "%d\n", j + 1);
        printf(THEME "^^^^^^^^^^^^\n\n");
      #endif
      #ifdef RAW_TRAIN
        print_perceptron(p);
        printf("\n");
      #endif
      error += fabs(train(p, d->data[j], learning_rate, d->targets[j]));
      #ifdef PRETTY_TRAIN
        printf(THEME "  test error: ");
        if (error < target_error) {
          printf(GREEN "%.7f", error);
        } else if (error > CLOSE) {
          printf(CLOSEC "%.7f", error);
        } else {
          printf(FARC "%.7f", error);
        }
        printf(THEME "\n");
      #endif
    }
    if (error < target_error) {
      #if defined(PRETTY) || defined(PRETTY_LEARN_OPTIMIZE)
        printf(THEME "\ntarget error reached on epoch ");
        printf(VARIABLE "%d", i + 1);
        printf(THEME ": ");
        printf(GREEN "%.7f", error);
        printf(THEME "  learning rate: ");
        printf(YELLOW "%.7f", learning_rate);
        printf(THEME "\n");
        print_perceptron(p);
        printf("\n\n");
      #endif
      #ifdef RAW
        printf(BLUE "%d ", i + 1);
        printf(GREEN "%.7f ", error);
        printf(YELLOW "%.7f\n", learning_rate);
      #endif
      #ifdef OUTPUT_EPOCH
        printf("%d\n", i);
      #endif
      return i;
    }
  }
  #ifdef PRETTY_TRAIN
    printf(THEME "\n");
    printf(THEME "target epoch ");
    printf(EPOCHC "%d", epochs);
    printf(THEME " reached with ");
    printf(THEME " epoch error: ");
    printf(RED "%.7f", error);
    #ifdef OUTPUT_LEARN
      printf(THEME "  learning rate: ");
      printf(ANSI_COLOR_YELLOW "%.7f", learning_rate);
    #endif
    printf(THEME "\n");
  #endif
  return epochs;
}

// print_perceptron(p) prints the perceptron to the console
// requires: p is not null
// effects: writes to the console
void print_perceptron(perceptron *p) {
  #ifndef RAW_TRAIN
    printf(THEME "  perceptron:  ");
  #endif
  for (int i = 0; i < p->input_amount; i++) {
    #ifndef RAW_TRAIN
      printf(THEME " | ");
    #endif
    if (p->weights[i] < 0) {
      printf(PERCEPTRONC "%.7f ", p->weights[i]);
    } else {
      printf(PERCEPTRONC " %.7f ", p->weights[i]);
    }
  }
  #ifndef RAW_TRAIN
    printf(THEME " |\n");
  #endif
}

// print_inputs(in) prints the inputs to the console
// requires: in is not null
// effects: writes to the console
void print_inputs(inputs *in) {
  printf(THEME "  inputs:      ");
  for (int i = 0; i < in->input_amount; i++) {
    printf(THEME " | ");
    if (in->data[i] < 0) {
      printf(INPUT "%.7f ", in->data[i]);
    } else {
      printf(INPUT " %.7f ", in->data[i]);
    }
  }
  printf(THEME " |\n");
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
