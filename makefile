IDIR = include
SDIR = src
ODIR = obj

CC = gcc
CFLAGS = -I$(IDIR) -Wall -O2

LIBS =

_DEPS = perceptron.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o perceptron.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

perceptron: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR):
	mkdir -p $(ODIR)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o perceptron
