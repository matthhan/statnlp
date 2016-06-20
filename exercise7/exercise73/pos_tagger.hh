#ifndef POS_TAGGER_HH
#define POS_TAGGER_HH
#include "annotated_sentence.hh"
#include "membership_model.hh"
#include "pos_bigram_model.hh"
#include "dictionary.hh"
#include <string>
#include <limits>
#include <algorithm>
#include "pos.hh"
#include "word.hh"

using std::string;
using std::numeric_limits;
using std::vector;
using std::reverse;

class PosTagger {
    public:
        PosTagger(Dictionary* wordDictionary,Dictionary* posDictionary);
        void trainOn(AnnotatedSentence s);
        void parsePosBigramModel(string filename);
        TagSequence tag(Sentence s);
        TagSequence tag_greedy(Sentence s);
        void refreshPossiblePoses();
    private:
        MembershipModel membershipModel;
        PosBigramModel posBigramModel;
        Dictionary* posDictionary;
        vector<double> getMembershipLogProbabilities(Word w);
        vector<double> getBigramLogProbabilities(Pos p);
        vector<Pos> possiblePoses;
        bool possiblePosesDirty;
};
#endif
