#ifndef POS_BIGRAM_MODEL_HH
#define POS_BIGRAM_MODEL_HH
#include <string>
#include <cmath>
#include <map>
#include <fstream>
#include <utility>
#include "dictionary.hh"
#include "pos.hh"
#include "file_io.hh"
using std::string;
using std::log;
using std::map;
using std::pair;
using std::ifstream;
using std::make_pair;

class PosBigramModel {
    public:
        PosBigramModel(Dictionary* posDictionary);
        void parseFromFile(string filename);
        double probability(Pos first,Pos second);
        double logProbability(Pos first,Pos second);
    private:
        Dictionary* posDictionary;
        map<Pos,double> fallbackUnigramModel;
        map<Pos,double> backoffWeights;
        map<pair<Pos,Pos>,double> bigramModel;
        void readUnigramModel(ifstream& stream);
        void readBigramModel(ifstream& stream);
};
#endif
