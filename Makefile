# comprog
CC      = g++
CCFLAGS = -g
.PHONY: clean all

SRCS := $(wildcard *.cc)
BINS := $(SRCS:%.cc=%.exe)

all: $(BINS)

%.exe: %.o
	$(CC) $< -o $@

%.o: $.cc
	$(CC) $(CCFLAGS) -c $<

clean:
	rm *.exe *.o
