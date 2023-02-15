# comprog
CXXC=g++
CXXCFLAGS=-g

SRCS:=$(wildcard *.cpp)
BINS:=$(SRCS:%.cpp=%.exe)

.PHONY += all
all: $(BINS)

%.exe: %.cpp
	$(CXXC) $(CXXCFLAGS) $< -o $@

.PHONY += clean
clean:
	rm *.exe
