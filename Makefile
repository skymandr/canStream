# Compiler:
CC = gcc

# Linking:
LDFLAGS = -lcanlib -lpthread

# Compiler optionsh
CFLAGS = -O3 -L. $(LDFLAGS)

# Objects:
OBJS = util.o

# Targets:
all:	upstream downstream sounddemo

upstream:	upstream.o $(OBJS)
	$(CC) -o $@ $(OBJS) upstream.o $(CFLAGS)

downstream:	downstream.o $(OBJS)
	$(CC) -o $@ $(OBJS) downstream.o $(CFLAGS)

sounddemo: sounddemo.o
	$(CC) -o $(@) sounddemo.o

clean:
	rm -f *.o

cleanall:	clean
	rm -f downstream upstream sounddemo a.out

# Suffixes:
.SUFFIXES:	.c
.c.o:
	$(CC) -c $< $(CFLAGS)
