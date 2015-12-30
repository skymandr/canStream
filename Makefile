# Compiler:
CC = gcc

# Linking:
LDFLAGS = -lcanlib -lpthread

# Compiler optionsh
CFLAGS = -O3 -L. $(LDFLAGS)

# Objects:
ODIR = objects
_OBJ = util.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# Targets:
all:	upstream downstream sounddemo

$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

upstream:	$(OBJ) upstream.o
	$(CC) -o $@ $^ $(CFLAGS)

downstream:	$(OBJ) downstream.o
	$(CC) -o $@ $^ $(CFLAGS)

sounddemo:
	$(CC) -o $@ sounddemo.c

.PHONY: clean cleanall

clean:
	rm -f *.o $(ODIR)/*.o

cleanall:	clean
	rm -f downstream upstream sounddemo a.out bin/*
