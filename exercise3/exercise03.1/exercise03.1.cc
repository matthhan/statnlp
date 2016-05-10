#include <iostream>
#include <unistd.h>
#include <ctype.h>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>

#include "multinomial_classifier.hh"
#include "dictionary.hh"
void printUsage();
std::string readLine(std::ifstream& stream) {std::string s;std::getline(stream,s); return s;}
bool canReadMore(std::ifstream& stream) {return !stream.eof();}
int main(int argc, char* argv[]) {
    std::string trainDataPath = "20news/20news.tr";
    std::string testDataPath = "20news/20news.te";
    std::string vocabPath = "20news/20news.voc";

    auto trainDataFile = std::ifstream(trainDataPath);
    auto dictionary = Dictionary();
    auto classifier = MultinomialClassifier(&dictionary);
    while(canReadMore(trainDataFile)) {
        std::string w = readLine(trainDataFile);
        Document doc = Document::parseFromLine(w,dictionary);
        classifier.trainOnDocument(doc);
    }
    trainDataFile.close();

    auto testDataFile = std::ifstream(testDataPath);
    int testDataConsidered = 0;
    int classifiedCorrectly = 0;
    while(canReadMore(trainDataFile)) {
        std::string w = readLine(trainDataFile);
        Document doc = Document::parseFromLine(w,dictionary);
        testDataConsidered++;
        if(classifier.classify(doc) == doc.realClass) classifiedCorrectly++;
    }
    /*
    //TODO:Make up new parameter names
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
    if(n<1 || filename== NULL) {printUsage();exit(0);}*/
}
void printUsage() {
    //TODO: Change in accordance with new parameters
    /*
    std::cout << "Usage: <program> -f <filename> -n <number of words>" << std::endl
        << "File must be formatted such that every line contains exactly one word" << std::endl
        << "and everything is lowercase" << std::endl;
        */
}
