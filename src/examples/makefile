

CXX = g++
DIR = ../include
CXXFLAGS = -std=c++11 -Wall -lfftw3 -I$(DIR)

# HEADERS = 

all:  signal_processing_example.exe IO_example.exe  
	./signal_processing_example.exe
	./IO_example.exe

signal_processing: signal_processing_example.exe 
	./signal_processing_example.exe


IO: IO_example.exe
	./IO_example.exe


%.exe: %.o
	$(CXX)  -o $@  $^ $(CXXFLAGS)

%_test.o : %_test.cpp $(DIR)/%.hpp
	$(CXX) -c $<  $(CXXFLAGS)

clean:
	rm -rf *.o *.exe

.phoney: clean all



# random_generators_test.exe: random_generators_test.o
# 	$(CXX)  -o $@  $^ $(CXXFLAGS)

# IO_test.exe: IO_test.o 
# 	$(CXX)  -o $@  $^ $(CXXFLAGS)

# timing_test.exe : timing_test.o
# 	$(CXX)  -o $@  $^ $(CXXFLAGS)
