#Compiler binary
CXX=g++
CXXFLAGS=-Wall -O2 -std=c++11
DONTLINKFLAG=-c
FINALRESULTNAME= program.out

all: exercise01.4

exercise01.4: dictionary.o occurence_counter.o word.hh exercise01.4.cc 
	$(CXX) $(CXXFLAGS) exercise01.4.cc dictionary.o occurence_counter.o -o $(FINALRESULTNAME)
dictionary.o: dictionary.cc dictionary.hh
	$(CXX) $(CXXFLAGS) $(DONTLINKFLAG) dictionary.cc 
occurence_counter.o: occurence_counter.cc occurence_counter.hh
	$(CXX) $(CXXFLAGS) $(DONTLINKFLAG) occurence_counter.cc 
.PHONY: clean veryclean
clean:
	rm -f *.o *.out
veryclean: clean
	rm -f *~

