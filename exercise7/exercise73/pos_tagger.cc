#include "pos_tagger.hh"
PosTagger::PosTagger() {
    this->posBigramModel = PosBigramModel();
    this->membershipModel = MembershipModel();
}
void PosTagger::trainOn(AnnotatedSentence s) {
    //TODO:implement
}
void PosTagger::parsePosBigramModel(string filename){
    //TODO:implement
}
TagSequence PosTagger::tag(Sentence s) {
    //TODO:implement
    return TagSequence();
}
