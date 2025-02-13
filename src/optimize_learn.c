
#include "optimize_learn.h"
#include <stdio.h>
#include <math.h>
#include "print_settings.h"
#include "color.h"

#define LEARNING_RATE 0.0001
#define POWER 4

// test_learn_range(learning_rate) returns the epochs reached fitting a perceptron
// requires: p and d are not null
float test_learn_range(perceptron *p, data *d, int epochs, float target_error) {
  int best = __INT_MAX__;
  float best_rate = 0;
  int current = 0;
  for (int i = 0; i <= POWER; i++) {
    for (int j = 1; j < 10; j++) {
      float test_rate = (LEARNING_RATE * (float) j) * pow(10.0, i);
      #ifdef OUTPUT_LEARN
        printf(THEME "test rate:    ");
        printf(YELLOW "%.7f", test_rate);
        printf(THEME "   ");
      #endif
      random_weights(p);
      current = fit(p, d, epochs, test_rate, target_error);
      #ifdef OUTPUT_LEARN
        printf("epochs:    ");
        if (current < epochs) {
          printf(GREEN "%d", current + 1);
        } else {
          printf(RED "%d", current);
        }
        printf(THEME "\n");
        #ifdef PRETTY
          if (current < epochs) {
            printf("\n");
          }
        #endif
      #endif
      if (best > current) {
        best = current;
        best_rate = test_rate;
      }
    }
  }
  #ifdef OUTPUT_LEARN
    printf("\nbest rate:    ");
    printf(GREEN "%.7f", best_rate);
    printf(THEME "   epochs:    ");
    printf(BLUE "%d", best);
    printf(THEME "\n");
  #endif
  return best_rate;
}
