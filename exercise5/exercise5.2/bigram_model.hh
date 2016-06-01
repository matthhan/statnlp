#ifndef BIGRAM_MODEL_HH
#define BIGRAM_MODEL_HH
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "file_io.hh"
#include "word.hh"
#include "dictionary.hh"

using std::map;
using std::string;
using std::pair;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::vector;
using std::stod;
using std::make_pair;

class BigramModel {
    public:
        BigramModel(string filePath,Dictionary& dict);
        double probability(Word s);
        double logProbability(Word s);
    private:
        BigramModel();
        Word lastReadWord;
        map<Word,pair<double,double>> fallbackUnigramModel;
        map<pair<Word,Word>,double> bigramModel;
        void readUnigramModel(ifstream& stream);
        void readBigramModel(ifstream& stream);
        Dictionary* dict;
};
#endif
