#ifndef MEMBERSHIP_MODEL_HH
#define MEMBERSHIP_MODEL_HH
#include "pos.hh"
#include "annotated_sentence.hh"
#include <cmath>

using std::log;

class MembershipModel {
    public:
        MembershipModel();
        void trainOn(Pos p,Word w);
        void trainOn(AnnotatedSentence s);
        double probability(Pos p,Word w);
        double logProbability(Pos p,Word w);
    private:
};
#endif
