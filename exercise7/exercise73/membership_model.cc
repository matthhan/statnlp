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
    for(auto tuple:s) this->trainOn(tuple.first,tuple.second);
}
double MembershipModel::probability(Pos p,Word w) {
    auto count = this->posSpecificWordCount[p][w] + 1;
    auto normalizingFactor = this->posCount[p] + this->wordDictionary->size();
    return count/normalizingFactor;
}
double MembershipModel::logProbability(Pos p,Word w) {
    return log(this->probability(p,w));
}
