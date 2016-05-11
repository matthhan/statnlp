#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

#include <cstdlib>
#include <ctype.h>
#include <unistd.h>

#include "multinomial_classifier.hh"
#include "dictionary.hh"

//Forward declarations
void printUsage();
std::map<std::string,std::string> parseCLIParams(int argc,char* argv[]);
void validateParams(std::map<std::string,std::string> params);
std::string readLine(std::ifstream& stream);
bool canReadMore(std::ifstream& stream);

int main(int argc, char* argv[]) {
    auto params = parseCLIParams(argc,argv);
    validateParams(params);
    std::string trainDataPath = params["trainDataPath"];
    std::string testDataPath = params["testDataPath"];
    std::string vocabPath = params["vocabPath"];

    auto trainDataFile = std::ifstream(trainDataPath);
    auto dictionary = Dictionary();
    auto classifier = MultinomialClassifier();
    

    int i = 1;
    std::cout << "Reading training data" << std::endl;
    while(canReadMore(trainDataFile)) {
        if((i%1000) == 0)std::cout << "" << i << ", " << std::flush;
        i++;
        std::string w = readLine(trainDataFile);
        Document doc = Document::parseFromLine(w,dictionary);
        classifier.trainOnDocument(doc);
    }
    std::cout << std::endl << "Finished Training Model" << std::endl;
    trainDataFile.close();

    auto testDataFile = std::ifstream(testDataPath);
    int testDataConsidered = 0;
    int classifiedCorrectly = 0;
    int rejections = 0;

    std::cout << "Classifying: " << std::endl;
    while(canReadMore(testDataFile)) {
        if(testDataConsidered % 100 == 0) std::cout << testDataConsidered << ", " << std::flush;
        std::string w = readLine(testDataFile);
        Document doc = Document::parseFromLine(w,dictionary);
        testDataConsidered++;
        auto res = classifier.classify(doc);
        if(res == doc.realClass) classifiedCorrectly++;
        if(res == "REJECT") rejections++;
    }
    std::cout << std::endl;
    double percentageClassifiedCorrectly = 
        (double)classifiedCorrectly/(double)testDataConsidered;
    std::cout << "Percentage classified correctly: " << 
        percentageClassifiedCorrectly << std::endl;
    std::cout << "Percentage rejected: " << 
        (double)rejections/(double) testDataConsidered << std::endl;
}

std::map<std::string,std::string> parseCLIParams(int argc,char* argv[]) {
    auto params = std::map<std::string,std::string>();
    int c;
    while((c = getopt(argc,argv,"r:t:v:")) != -1) {
        switch (c) {
            case 'r':
               params["trainDataPath"] = optarg;
               break;
           case 't':
               params["testDataPath"] = optarg;
               break;
           case 'v':
               params["vocabPath"] = optarg;
               break;
           case '?':
               printUsage();
               exit(1);
           default:
               printUsage();
               exit(1);
        } 
    }
    return params;
}
void validateParams(std::map<std::string,std::string> params) {
    if((params["trainDataPath"] == "") || 
            (params["testDataPath"] == "") || 
            (params["vocabPath"] == "") ) {
        printUsage();
        exit(1);
    }
}
void printUsage() {
    std::cout << "Usage: <program> -r <file-with-training-data> -t <file-with-test-data> -v <file-with-vocabulary>" << std::endl;
}
std::string readLine(std::ifstream& stream) {
    std::string s;std::getline(stream,s); return s;
}
bool canReadMore(std::ifstream& stream) {
    return !stream.eof();
}
