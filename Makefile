# Compiler:
CC = gcc

# Linking:
LDFLAGS = -lcanlib -lpthread

# Compiler optionsh
CFLAGS = -O3 -L. $(LDFLAGS)

# Objects:
OBJS = util.o

# Targets:
all:	upstream downstream clean

upstream:	upstream.o $(OBJS)
	$(CC) -o $@ $(OBJS) upstream.o $(CFLAGS)

downstream:	downstream.o $(OBJS)
	$(CC) -o $@ $(OBJS) downstream.o $(CFLAGS)

clean:
	rm -f *.o

cleanall:	clean
	rm -f downstream upstream a.out

# Suffixes:
.SUFFIXES:	.c
.c.o:
	$(CC) -c $< $(CFLAGS)
