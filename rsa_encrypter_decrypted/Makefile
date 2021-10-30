CXX = g++
CPPFLAGS = -g -Wall

all: rsa

doublet: rsa.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf rsa
