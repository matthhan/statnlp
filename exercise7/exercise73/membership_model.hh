#ifndef MEMBERSHIP_MODEL_HH
#define MEMBERSHIP_MODEL_HH
#include "pos.hh"
#include "annotated_sentence.hh"
#include <cmath>
#include <map>
#include <utility>

using std::log;
using std::map;

class MembershipModel {
    public:
        MembershipModel(Dictionary* wordDictionary);
        void trainOn(Pos p,Word w);
        void trainOn(AnnotatedSentence s);
        double probability(Pos p,Word w);
        double logProbability(Pos p,Word w);
    private:
        map<Pos,map<Word,int>> posSpecificWordCount;    
        map<Pos,int> posCount;
        Dictionary* wordDictionary;
};
#endif
