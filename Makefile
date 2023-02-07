# comprog

CC      = cl
CCFLAGS = /std:c++20 /Zi /MT /EHsc

SRCS  = $(wildcard *.cc)
MAINS = $(patsubst %.cc, %.exe, $(SRC))

.PHONY: clean all


all: $(MAINS)

%.exe: $(SRCS)
	$(CC) $(CCFLAGS) $< /Fe $@

clean:
	rm *.exe
