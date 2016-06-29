//This is the same file as task4_3_b.cc except for the #defines at the beginning
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

//These are the only lines that are different in (c)
#define SUBSTITUTION_PENALTY 4
#define INSERTION_PENALTY 3
#define DELETION_PENALTY 3


using namespace std;

// definition of data types
typedef std::string Word;
typedef std::vector<Word> WordList;
typedef std::vector<WordList> SentenceList;

enum EditOperation {NO, SUB, INS, DEL};
struct AlignmentElement {
    Word spoken;
    Word recog;
    EditOperation operation;

    AlignmentElement(const Word & spoken, const Word & recog, EditOperation operation) :
	spoken(spoken), recog(recog), operation(operation) {}
};
typedef std::vector<AlignmentElement> Alignment;

//We added this type to be able to return two arrays: one with the minimum distances to each
//point and one with the backpointers, so that we will still be able to know which path was
//the optimal one. There is probably a more elegant way to do this, but we're new to C++.
struct DistsAndChoices {
    vector<vector<int> > minDists;
    vector<vector<int> > choices;
};
//Functions we Inserted. Otherwise, we only changed main()
DistsAndChoices findPaths(WordList spoken,WordList recognized);
//Finds the best alignment
int min3(int a,int b, int c);
//returns the smallest of the variables
int argmin3(int a,int b, int c);
//returns 1 if a is smallest, 2 if b is smallest, 3 if c is smallest
vector<int> findOptimalPath(vector<vector<int> > arr);
//Input: an array with optimal paths from beginning to any Point in the lattice
//Output an array with values 0-3 describing the optimal path 
//from beginning to end in terms of substitutions, deletions and insertions
Alignment alignmentFromOptimalPath(vector<int> optPath,WordList spoken,WordList recognized);
//Turns An optimal path vector as returned by findOptimalPath() into an easily printable Alignment



// i/o-functionality
void readSentences(std::ifstream & is, SentenceList & s);
void levenshteinAlign(const Alignment & a, std::ostream & o);


// main
void usage();
int main(int argc, char* argv[]);




// -----------------------------------------------------------------------------
// i/o-functionality

void readSentences(std::ifstream & is, SentenceList & sentences) {
    std::string buffer;
    Word word;
    while (std::getline(is, buffer)) {
	if (buffer.size() == 0) 
	    continue;
	std::istringstream line(buffer.c_str());
	WordList sentence;
	while (line >> word) 
	    sentence.push_back(word);
	sentences.push_back(sentence);
    }
}

/*
  How to use writeAlignment:

  1: Alignment alignment;
  2: alignment.push_back(AlignmentElement("HELLO", "HOW", SUB));
  3: alignment.push_back(AlignmentElement("",      "LOW", INS));
  4: writeAlignment(alignment, std::cout);
*/
void writeAlignment(const Alignment & alignment, std::ostream & os) {
    std::ostringstream ossSpoken, ossRecog, ossOperation;
    int length;
    for (Alignment::const_iterator itAlignment = alignment.begin();
	 itAlignment != alignment.end(); ++itAlignment)
	switch (itAlignment->operation) {
	case NO:
	    length = std::max(itAlignment->spoken.size(), itAlignment->recog.size()) + 1;
	    ossSpoken    << std::left << std::setw(length) << itAlignment->spoken;
	    ossRecog     << std::left << std::setw(length) << itAlignment->recog;
	    ossOperation << std::left << std::setw(length) << " ";
	    break;
	case SUB:
	    length = std::max(itAlignment->spoken.size(), itAlignment->recog.size()) + 1;
	    ossSpoken    << std::left << std::setw(length) << itAlignment->spoken;
	    ossRecog     << std::left << std::setw(length) << itAlignment->recog;
	    ossOperation << std::left << std::setw(length) << "S";
	    break;
	case INS:
	    length = itAlignment->recog.size() + 1;
	    ossSpoken    << std::left << std::setw(length) << " ";
	    ossRecog     << std::left << std::setw(length) << itAlignment->recog;
	    ossOperation << std::left << std::setw(length) << "I";
	    break;
	case DEL:
	    length = itAlignment->spoken.size() + 1;
	    ossSpoken    << std::left << std::setw(length) << itAlignment->spoken;
	    ossRecog     << std::left << std::setw(length) << " ";
	    ossOperation << std::left << std::setw(length) << "D";
	    break;
	}
    os << std::endl;
    os << ossSpoken.str()    << std::endl;
    os << ossRecog.str()     << std::endl;
    os << ossOperation.str() << std::endl;
}






// -----------------------------------------------------------------------------
// main

void usage(const char * basename) {
    std::cerr << " usage: " << basename 
	      << " <spoken-sentences-file> <recognized-sentences-file>" 
	      << std::endl;
    std::exit(1);
}

int main(int argc, char* argv[]){
    // check for correct number of command line arguments
    if (argc != 3)
	usage(argv[0]);


    // read spoken and recognized sentences from files
    SentenceList spoken, recog;
    {
	std::ifstream spokenStream(argv[1]);
	if (!spokenStream) {
	    std::cerr << std::endl << "ERROR: " << argv[1] << " could not be opened" 
		      << std::endl;
	    return 2;
	}
	std::ifstream recogStream(argv[2]);
	if (!recogStream) {
	    std::cerr << std::endl << "ERROR: " << argv[2] << " could not be opened" 
		      << std::endl;
	    return 2;
	}

	readSentences(spokenStream, spoken);
	readSentences(recogStream, recog);
	if (spoken.size() != recog.size()){
	    std::cerr << std::endl << "ERROR: Number of sentences do not match!" 
		      << " (" << spoken.size() << "/" << recog.size() << ")" 
		      << std::endl;
	    return 3;
	}
    }

    // ... <your code>
    //Calculate and output the WERS for each individual sentence and then calculate and output
    //their sum.
    vector<int> wer;
    for(int i = 0;i < spoken.size();i++) {
       //Calculates the optimal Paths and minimum Distances
       DistsAndChoices d = findPaths(spoken[i],recog[i]);
       //The WER for i is in the "top right" corner of the table with the minimal distances
       int weri = d.minDists[d.minDists.size()-1][d.minDists[d.minDists.size()-1].size()-1];
       cout << "The WER for Sentence " << i << " is " << weri << "." << endl;
       wer.push_back(weri);
    }
    int sum = 0;
    for(int i = 0; i < wer.size();i++) {
        sum += wer[i];
    }
    cout << "The sum of the WERs of all sentences is " << sum << "." << endl;
    return 0;
}



int min3(int a,int b, int c) {
    return min(a,min(b,c));
}

int argmin3(int a,int b,int c) {
    int m = min3(a,b,c);
    if(m == a) return 1;
    else if(m == b) return 2;
    else return 3;
}


DistsAndChoices findPaths(WordList spoken,WordList recognized) {
   vector<vector<int> > minDists;//minDists[i][j] contains the minimal path to align the WordLists up to i and j
   vector<vector<int> > choices;//choices[i][j] contains which one of the edit 
                                //operations was undertaken last
                                //1 stands for substitution/no edit
                                //2 stands for insertion
                                //3 stands for deletion
    //Sets up empty arrays
    for(int i = 0;i < recognized.size();i++) {
        minDists.push_back(vector<int>());
        choices.push_back(vector<int>());
        for(int j = 0;j < spoken.size();j++) {
            minDists[i].push_back(0);
            choices[i].push_back(numeric_limits<int>::max());
        }
    }
    //In these nested for-loops, the minimal distance and the partially optimal paths are calculated
    for(int i = 0;i < minDists.size();i++) {//columns, then rows
        for(int j = 0;j < minDists[0].size();j++) {
           int neq;
           //cout << "i: " << i << "j: " << j << endl;
           //We need to know whether the spoken and the 
           //recognized words are equal
           if(recognized[i] == spoken[j]) {
                neq = 0;
           }
           else {
                neq = 1;
           }
           //corner case where we are in the bottom left corner
           if(i == 0 && j == 0)  {
                minDists[i][j] = neq;
                choices[i][j] = 1;
           }
           //corner case where we are in the leftmost column
           else if(i == 0) {
                minDists[i][j] = neq + minDists[i][j-1];
                choices[i][j] = 3;
           }
           //corner case where we are in the lowest row
           else if(j == 0) {
                minDists[i][j] = neq + minDists[i-1][j];
                choices[i][j] = 2;
           }
           //The normal case
           else{
               minDists[i][j] = neq + min3(minDists[i-1][j-1]+SUBSTITUTION_PENALTY,
                                          minDists[i-1][j]+INSERTION_PENALTY, 
                                          minDists[i][j-1]+DELETION_PENALTY); 
               choices[i][j] = argmin3(minDists[i-1][j-1],
                                            minDists[i-1][j], 
                                            minDists[i][j-1]);
               if(choices[i][j] == 1 && neq == 0) {
                    choices[i][j] = 0; //No substitution
               }
           }
        }
    }
    DistsAndChoices res;
    res.minDists = minDists;
    res.choices = choices;
    return res;
}

vector<int> findOptimalPath(vector<vector<int> > arr){
    vector<int> bestChoices;
    int i = arr.size()-1;
    int j = arr[i].size()-1;
    while(!(i == 0 && j == 0)) {
        bestChoices.insert(bestChoices.begin(),arr[i][j]);
        if(bestChoices[0] == 1 || bestChoices[0] == 0) {
            i--;j--;
        }
        else if(bestChoices[0] == 2) {
            i--;
        }
        else if(bestChoices[0] == 3) {
            j--;
        }
    }
    return bestChoices;
}

Alignment alignmentFromOptimalPath(vector<int> optPath,WordList spoken,WordList recognized) {
    Alignment al;
    al.push_back(AlignmentElement(spoken[0],recognized[0],NO));
    int i = 0;int j = 0;
    for(int k = 0;k < optPath.size();k++) {
       if(optPath[k] == 0) {
            i++;j++;
            al.push_back(AlignmentElement(spoken[i],recognized[j],NO));
       } 
       else if(optPath[k] == 1) {
            i++;j++;
            al.push_back(AlignmentElement(spoken[i],recognized[j],SUB));
       }
       else if(optPath[k] == 2) {
            j++;
            al.push_back(AlignmentElement("",recognized[j],INS));
       }
       else if(optPath[k] == 3) {
            i++;
            al.push_back(AlignmentElement(spoken[i],"",DEL));
       }
    }
    return al;
}
