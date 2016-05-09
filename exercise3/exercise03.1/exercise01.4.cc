#include <iostream>
#include "word.hh"
#include "dictionary.hh"
#include "occurence_counter.hh"
#include <unistd.h>
#include <ctype.h>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>

void printUsage();
Word readWord(std::ifstream& stream) {std::string s;std::getline(stream,s); return s;}
bool canReadMore(std::ifstream& stream) {return !stream.eof();}
int main(int argc, char* argv[]) {
    //Handle Arguments
    int c;
    int n = -1;
    char* filename = NULL;
    while((c = getopt(argc,argv,"n:f:")) != -1) {
        switch (c) {
            case 'n':
               n=atoi(optarg);
               break;
           case 'f':
               filename =optarg;
               break;
           case '?':
               printUsage();
               exit(0);
           default:
               exit(0);
        } 
    }
    if(n<1 || filename== NULL) {printUsage();exit(0);}

    //Read Words and count occurences
    auto input = std::ifstream(filename);
    auto dic = Dictionary();
    auto counter = OccurenceCounter();
    auto textAsIndices = std::vector<int>();
    while(canReadMore(input)) {
        Word w = readWord(input);
        int insertedAt = dic.insert(w);
        counter.addToCount(insertedAt);
        textAsIndices.push_back(insertedAt);
    }
    input.close();
    //Get most frequent pairs and print the text with them inserted
    auto frequentPairs = counter.getNMostFrequent(n);
    for(auto index:textAsIndices) {
        bool inMostFrequentWords = false;
        for(auto pair:frequentPairs) {
            if(index == pair.first) {inMostFrequentWords =true;break;}
        }
        if(inMostFrequentWords) std::cout << dic.getWordForIndex(index) << " ";
        else std::cout << "<UNK>";
    }
}
void printUsage() {
    std::cout << "Usage: <program> -f <filename> -n <number of words>" << std::endl
        << "File must be formatted such that every line contains exactly one word" << std::endl
        << "and everything is lowercase" << std::endl;
}
