#ifndef PERCEPTRON
#define PERCEPTRON

typedef struct {
  int input_amount;
  float *weights;
  float bias;
} perceptron;

perceptron * init_perceptron(int input_amount, float bias);
void delete_perceptron();

#endif
