#include "pos_tagger.hh"
PosTagger::PosTagger(Dictionary* wordDictionary,Dictionary* posDictionary) : 
    membershipModel(wordDictionary), 
    posBigramModel(posDictionary) {}
void PosTagger::trainOn(AnnotatedSentence s) {
    this->membershipModel.trainOn(s);
}
void PosTagger::parsePosBigramModel(string filename){
    this->posBigramModel.parseFromFile(filename);
}
TagSequence PosTagger::tag(Sentence s) {
    //TODO:implement
    return TagSequence();
}
