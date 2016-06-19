#Compiler binary
CXX=g++
CXXFLAGS=-Wall -std=c++11 -O2 
DONTLINKFLAG=-c
FINALRESULTNAME= program.out

#A wildcard that matches all already compiled object files
SRCS= $(wildcard *.cc)
OBJS= $(SRCS:.cc=.o)

#Makes the final project by linking together all oject files. 
finalresult: exercise73.o
exercise73.o: exercise73.cc $(OBJS)
	$(CXX) -o $(FINALRESULTNAME) $(CXXFLAGS) $^ 
pos_tagger.o: pos_tagger.cc pos_tagger.hh pos_bigram_model.o membership_model.o
#General rule to make an object file with no dependencies
%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(DONTLINKFLAG) $*.cc 
.PHONY: clean veryclean
clean:
	rm -f *.o *.out *.gch
veryclean: clean
	rm -f *~

