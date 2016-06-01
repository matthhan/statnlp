#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

#include "bigram_model.hh"
#include "file_io.hh"
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::getline;
int main(int argc,char* argv[]) {
    string dataPath = "../tc-star";
    string modelPath = "language_model.lm";

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
            Word w = dict.getWordForString(st);
            sumLogProbabilities += lm.logProbability(w);
            N++;
            cout << N << ", "<< endl;
        }
    }
    double logPerplexity = -(1/N) * sumLogProbabilities;
    double perplexity = pow(10,logPerplexity);
    cout << "Perplexity: " << perplexity << endl;
    return 0;
}


