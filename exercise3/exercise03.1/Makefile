#Compiler binary
CXX=g++
CXXFLAGS=-Wall -O2 -std=c++11
DONTLINKFLAG=-c
FINALRESULTNAME= program.out

dictionary.o: dictionary.cc dictionary.hh
	$(CXX) $(CXXFLAGS) $(DONTLINKFLAG) dictionary.cc 
occurence_counter.o: occurence_counter.cc occurence_counter.hh
	$(CXX) $(CXXFLAGS) $(DONTLINKFLAG) occurence_counter.cc 
class_counter.o: class_counter.cc class_counter.hh
	$(CXX) $(CXXFLAGS) $(DONTLINKFLAG) class_counter.cc 
.PHONY: clean veryclean
clean:
	rm -f *.o *.out
veryclean: clean
	rm -f *~

