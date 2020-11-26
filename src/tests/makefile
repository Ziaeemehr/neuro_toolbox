

CXX = g++
CXXFLAGS = -std=c++11 -Wall -I../include/

all: IO_test.exe timing_test.exe

IO_test.exe: IO_test.o 
	$(CXX)  -o $@  $^ $(CXXFLAGS)

timing_test.exe : timing_test.o
	$(CXX)  -o $@  $^ $(CXXFLAGS)

%.o : %.cpp neuro_toolbox.hpp 
	$(CXX) -c $<  $(CXXFLAGS)

clean:
	rm -rf *.o *.exe

.phoney: clean all

