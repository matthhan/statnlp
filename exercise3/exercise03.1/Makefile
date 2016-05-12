#Compiler binary
CXX=g++
CXXFLAGS=-Wall -std=c++11 -O2 
DONTLINKFLAG=-c
FINALRESULTNAME= program.out

#A wildcard that matches all already compiled object files
SRCS= $(wildcard *.cc)
OBJS= $(SRCS:.cc=.o)

#Makes the final project by linking together all oject files. 
finalresult: exercise03.1.o
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(FINALRESULTNAME)
exercise03.1.o: exercise03.1.cc multinomial_classifier.o dictionary.o document.o confusion_matrix.o
	$(CXX) $(CXXFLAGS) $(DONTLINKFLAG) $*.cc
multinomial_classifier.o: multinomial_classifier.cc multinomial_classifier.hh dictionary.o class_counter.o multinomial_model.o document.o 
	$(CXX) $(CXXFLAGS) $(DONTLINKFLAG) $*.cc
multinomial_model.o: multinomial_model.cc multinomial_model.hh occurence_counter.o
	$(CXX) $(CXXFLAGS) $(DONTLINKFLAG) $*.cc
#General rule to make an object file with no dependencies
%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(DONTLINKFLAG) $*.cc 
.PHONY: clean veryclean
clean:
	rm -f *.o *.out *.gch
veryclean: clean
	rm -f *~

