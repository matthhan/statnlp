#ifndef POS_TAGGER_HH
#define POS_TAGGER_HH
#include "annotated_sentence.hh"
#include "membership_model.hh"
#include "pos_bigram_model.hh"
#include "dictionary.hh"
#include <string>
using std::string;

class PosTagger {
    public:
        PosTagger(Dictionary* wordDictionary,Dictionary* posDictionary);
        void trainOn(AnnotatedSentence s);
        void parsePosBigramModel(string filename);
        TagSequence tag(Sentence s);
    private:
        PosBigramModel posBigramModel;
        MembershipModel membershipModel;

};
#endif
