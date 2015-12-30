# Compiler:
CC = gcc

# Directories:
ODIR = objects
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

$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

upstream:	$(OBJ) $(ODIR)/upstream.o
	$(CC) -o $@ $^ $(CFLAGS)

downstream:	$(OBJ) $(ODIR)/downstream.o
	$(CC) -o $@ $^ $(CFLAGS)

sounddemo:
	$(CC) -o $@ $(SRCDIR)/sounddemo.c

.PHONY: clean cleanall

clean:
	rm -f $(ODIR)/*.o

cleanall:	clean
	rm -f upstream downstream sounddemo
