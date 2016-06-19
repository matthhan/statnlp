#include "membership_model.hh"
MembershipModel::MembershipModel(Dictionary* wordDictionary) {
    this->posCount = map<Pos,int>();
    this->wordDictionary = wordDictionary;
}
void MembershipModel::trainOn(Pos p,Word w) {
    this->posCount[p]++;
    this->posSpecificWordCount[p][w]++;
}
void MembershipModel::trainOn(AnnotatedSentence s) {
    for(auto tuple:s) this->trainOn(tuple.second,tuple.first);
}
double MembershipModel::probability(Pos p,Word w) {
    double count = (double)this->posSpecificWordCount[p][w] + 1;
    auto normalizingFactor = (double)this->posCount[p] + (double)this->wordDictionary->size();
    return (double)count/(double)normalizingFactor;
}
double MembershipModel::logProbability(Pos p,Word w) {
    return log(this->probability(p,w));
}
