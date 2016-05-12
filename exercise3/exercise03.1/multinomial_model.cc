#include "multinomial_model.hh"
void MultinomialModel::updateFrequencies(Document &doc) {
    std::string klass = doc.realClass;
    for(auto indexFrequencyTuple:doc.contentFrequencies) {
        int index = indexFrequencyTuple.first;
        int frequency = indexFrequencyTuple.second;
        this->classConditionalProbabilities[klass].addToCount(index,frequency);
    }
}

MultinomialModel::MultinomialModel() {
    this->classConditionalProbabilities = 
        std::map<std::string,OccurenceCounter>();
    this->smoothed =false;
    this->dictionary = 0;
}
double MultinomialModel::getClassConditionalLogProbability(Document &doc,
        std::string klass) {
    double countVectorLogProbability = 0;
    for(auto tupl:doc.contentFrequencies) {
        int word = tupl.first;
        int count = tupl.second;
        double probability;
        if(!this->smoothed) probability = this->classConditionalProbabilities[klass].getProbability(word);
        else probability = this->classConditionalProbabilities[klass].getSmoothedProbability(word,this->dictionary->size());
        countVectorLogProbability += std::log(probability)*count;
    }
    return countVectorLogProbability;
}
void MultinomialModel::enableSmoothing(Dictionary* dictionary) {
    this->smoothed = true;
    this->dictionary = dictionary;
}
