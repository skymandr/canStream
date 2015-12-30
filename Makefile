# Compiler:
CC = gcc

# Directories:
ODIR = objects
BINDIR = bin
IDIR = inc
SRCDIR = src

# Linking:
LDFLAGS = -lcanlib -lpthread

# Compiler optionsh
CFLAGS = -O3 -L. $(LDFLAGS) -I$(IDIR)

# Objects:
_OBJ = util.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Targets:
all:	upstream downstream sounddemo

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

upstream:	$(OBJ) $(ODIR)/upstream.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

downstream:	$(OBJ) $(ODIR)/downstream.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

sounddemo:
	$(CC) -o $(BINDIR)/$@ sounddemo.c

.PHONY: clean cleanall

clean:
	rm -f $(ODIR)/*.o

cleanall:	clean
	rm -f bin/*
