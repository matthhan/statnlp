#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctype.h>
#include <unistd.h>

#include "bigram_model.hh"
#include "file_io.hh"
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
using std::map;
void printUsage();
map<string,string> parseCLIParams(int argc,char* argv[]);
void validateParams(map<string,string> params);
int main(int argc,char* argv[]) {
    auto params = parseCLIParams(argc,argv);
    validateParams(params);
    string dataPath = params["testDataPath"];
    string modelPath = params["modelPath"];

    Dictionary dict = Dictionary();
    auto lm = BigramModel(modelPath,dict);
    double sumLogProbabilities = 0;
    int N = 0;
    auto dataFile = ifstream(dataPath);
    cout << "Calculating Perplexity" << endl;
    cout << "Words considered: " << endl;
    while(canReadMore(dataFile)) {
        string line = readLine(dataFile);
        for(auto st:splitAt(line,' ')) {
            if (st=="") break;
            Word w = dict.getWordForString(st);
            sumLogProbabilities += lm.logProbability(w);
            N++;
            if(N%1000000==0) cout << N << ", "<< endl;
        }
    }
    double logPerplexity = -(1.0/(double)N) * sumLogProbabilities;
    double perplexity = pow(10,logPerplexity);
    cout << "sumLogProbabilities: " << sumLogProbabilities << endl;
    cout << "logPerplexity: " << logPerplexity << endl;
    cout << "Perplexity: " << perplexity << endl;
    return 0;
}


map<string,string> parseCLIParams(int argc,char* argv[]) {
    auto params = map<string,string>();
    int c;
    while((c = getopt(argc,argv,"m:t:")) != -1) {
        switch (c) {
           case 'm':
               params["modelPath"] = optarg;
               break;
           case 't':
               params["testDataPath"] = optarg;
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
    if((params["modelPath"] == "") || 
            (params["testDataPath"] == "")) {
        printUsage();
        exit(1);
    } 
}
void printUsage() {
    cout << "Usage: <program> -m <file-with-model> -t <file-with-test-data>" << endl;
}
