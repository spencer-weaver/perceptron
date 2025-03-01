IDIR = include
SDIR = src
ODIR = obj

CC = gcc
CFLAGS = -I$(IDIR) -Wall -O2

LIBS = -lm

_DEPS = perceptron.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o perceptron.o optimize_learn.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS) | $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

perceptron: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test-and: perceptron
	cat test_data/and.in test_data/and.expect | ./perceptron

test-even-odd: perceptron
	cat test_data/even_odd.in test_data/even_odd.expect | ./perceptron

$(ODIR):
	mkdir -p $(ODIR)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o perceptron
