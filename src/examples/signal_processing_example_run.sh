g++ -c signal_processing_example.cpp  -std=c++11 -Wall -lfftw3 #-I../include
g++  -o signal_processing_example.exe  signal_processing_example.o -std=c++11 -Wall -lfftw3 #-I../include
./signal_processing_example.exe 

