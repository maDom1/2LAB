# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Default build target
all: test demo

# Build test program
test: test.o Queap.o
	$(CXX) $(CXXFLAGS) -o test test.o Queap.o

# Build demo program
demo: demo.o Queap.o
	$(CXX) $(CXXFLAGS) -o demo demo.o Queap.o

# Object files
test.o: test.cpp Queap.h
	$(CXX) $(CXXFLAGS) -c test.cpp

demo.o: demo.cpp Queap.h
	$(CXX) $(CXXFLAGS) -c demo.cpp

Queap.o: Queap.cpp Queap.h
	$(CXX) $(CXXFLAGS) -c Queap.cpp

# Run targets
run-test: test
	./test | tee test_output.txt

run-demo: demo
	./demo

clean:
	rm -f *.o test demo test_output.txt

rebuild: clean all