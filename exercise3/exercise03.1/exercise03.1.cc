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
#include "confusion_matrix.hh"

//Forward declarations
void printUsage();
std::map<std::string,std::string> parseCLIParams(int argc,char* argv[]);
void validateParams(std::map<std::string,std::string> params);
std::string readLine(std::ifstream& stream);
bool canReadMore(std::ifstream& stream);
void buildVocabulary(Dictionary &dict,std::string vocabPath);

int main(int argc, char* argv[]) {
    //Parameter handling
    auto params = parseCLIParams(argc,argv);
    validateParams(params);
    std::string trainDataPath = params["trainDataPath"];
    std::string testDataPath = params["testDataPath"];
    std::string vocabPath = params["vocabPath"];
    bool quiet = params["q"] == "true";
    bool smoothed = params["s"] == "true";
    bool outputConfusionMatrix = params["c"] == "true";
    bool outputPercentages = params["p"] == "true";
    //If a vocabulary path was specified, insert the vocabulary
    //into the dictionary and prevent further changes to the dictionary.
    auto dictionary = Dictionary();
    if(!quiet) std::cout << "Built the Dictionary." << std::endl;
    if(vocabPath != "") buildVocabulary(dictionary,vocabPath);

    //Train the Model
    auto classifier = MultinomialClassifier();
    if(smoothed) classifier.enableSmoothing(&dictionary);
    auto trainDataFile = std::ifstream(trainDataPath);
    int i = 1;
    if(!quiet) std::cout << "Reading training data." << std::endl;
    while(canReadMore(trainDataFile)) {
        if(!quiet && (i%1000) == 0)std::cout << "" << i << ", " << std::flush;
        i++;
        std::string w = readLine(trainDataFile);
        Document doc = Document::parseFromLine(w,dictionary);
        classifier.trainOnDocument(doc);
    }
    if(!quiet) std::cout << std::endl << "Finished Training Model." << std::endl;
    trainDataFile.close();

    //Test the model
    auto testDataFile = std::ifstream(testDataPath);
    auto confusionMatrix = ConfusionMatrix();
    int testDataConsidered = 0;
    if(!quiet) std::cout << "Classifying. " << std::endl;
    while(canReadMore(testDataFile)) {
        if(!quiet && testDataConsidered % 1000 == 0) std::cout << testDataConsidered << ", " << std::flush;
        std::string w = readLine(testDataFile);
        Document doc = Document::parseFromLine(w,dictionary);
        testDataConsidered++;
        auto res = classifier.classify(doc);
        confusionMatrix.insert(doc.realClass,res);
    }
    testDataFile.close();
    double percentageClassifiedCorrectly = confusionMatrix.percentageClassifiedCorrectly();
    double percentageRejected = confusionMatrix.percentageRejected();
    if(!quiet) {
        std::cout << std::endl; 
        std::cout << "Percentage classified correctly: " << percentageClassifiedCorrectly << std::endl;
        std::cout << "Percentage rejected: " << percentageRejected << std::endl;
    }
    if(outputPercentages) std::cout << percentageClassifiedCorrectly << "," << percentageRejected << std::endl;
    if(outputConfusionMatrix) { 
        std::cout << confusionMatrix.toString() << std::endl;
    }
}

std::map<std::string,std::string> parseCLIParams(int argc,char* argv[]) {
    auto params = std::map<std::string,std::string>();
    int c;
    params["q"] = "false";
    params["s"] = "false";
    params["c"] = "false";
    params["p"] = "false";
    while((c = getopt(argc,argv,"r:t:v:qscp")) != -1) {
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
           case 'q':
               params["q"] = "true";
               break;
           case 's':
               params["s"] = "true";
               break;
           case 'c':
               params["c"] = "true";
               break;
           case 'p':
               params["p"] = "true";
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
            (params["testDataPath"] == "")) {
        printUsage();
        exit(1);
    } 
    if((params["vocabPath"] == "")) {
        std::cout << "No vocabulary specified!" << std::endl;
        std::cout << "Using full vocabulary, i.e. every word is in the dictionary." << std::endl;
    }
}
void printUsage() {
    std::cout << "Usage: <program> -r <file-with-training-data> -t <file-with-test-data> -v <file-with-vocabulary>" << std::endl;
    std::cout << "-q: suppress default outputs" << std::endl;
    std::cout << "-s: use simple smoothing" << std::endl;
    std::cout << "-c: output a confusion matrix" << std::endl;
    std::cout << "-p: output percentages correctly classified and rejected in simple, comma separated form" << std::endl;
}
std::string readLine(std::ifstream& stream) {
    std::string s;std::getline(stream,s); return s;
}
bool canReadMore(std::ifstream& stream) {
    return !stream.eof();
}
void buildVocabulary(Dictionary &dict,std::string vocabPath) {
    auto vocabFile = std::ifstream(vocabPath);
    while(canReadMore(vocabFile)) {
        std::string w = readLine(vocabFile);
        dict.insert(w);
    }
    dict.makeImmutable();
    vocabFile.close();
}
