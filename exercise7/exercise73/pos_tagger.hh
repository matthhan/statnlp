#ifndef POS_TAGGER_HH
#define POS_TAGGER_HH
#include "annotated_sentence.hh"
#include "membership_model.hh"
#include "pos_bigram_model.hh"
#include "dictionary.hh"
#include <string>
#include <limits>
#include "pos.hh"
#include "word.hh"

using std::string;
using std::numeric_limits;

class PosTagger {
    public:
        PosTagger(Dictionary* wordDictionary,Dictionary* posDictionary);
        void trainOn(AnnotatedSentence s);
        void parsePosBigramModel(string filename);
        TagSequence tag(Sentence s);
        void refreshPossiblePoses();
    private:
        PosBigramModel posBigramModel;
        MembershipModel membershipModel;
        Dictionary* posDictionary;
        vector<double> getMembershipLogProbabilities(Word w);
        vector<double> getBigramLogProbabilities(Pos p);
        vector<Pos> possiblePoses;
        bool possiblePosesDirty;
};
#endif
