#include "pos_bigram_model.hh"
PosBigramModel::PosBigramModel() {
    //TODO:implement
}
void PosBigramModel::parseFromFile(string filename,Dictionary posDictionary) {
    //TODO:implement
}
double PosBigramModel::probability(Pos first,Pos second) {
    //TODO:implement
    return 0;
}
double PosBigramModel::logProbability(Pos first,Pos second) {
    return log(this->probability);
}
