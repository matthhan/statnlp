#include "membership_model.hh"
MembershipModel::MembershipModel() {
    
}
void MembershipModel::trainOn(Pos p,Word w) {
    //TODO:implement
}
void MembershipModel::trainOn(AnnotatedSentence s) {
    for(auto tuple:s) this->trainOn(tuple.first,tuple.second);
}
double MembershipModel::probability(Pos p,Word w) {
    //TODO:implement
    return 0;
}
double MembershipModel::logProbability(Pos p,Word w) {
    return log(this->probability);
}
