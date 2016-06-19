#ifndef POS_BIGRAM_MODEL_HH
#define POS_BIGRAM_MODEL_HH
#include <string>
#include <cmath>
#include "dictionary.hh"
#include "pos.hh"
using std::string;
using std::log;

class PosBigramModel {
    public:
        PosBigramModel();
        void parseFromFile(string filename,Dictionary posDictionary);
        double probability(Pos first,Pos second);
        double logProbability(Pos first,Pos second);
    private:
};
#endif
