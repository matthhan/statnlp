#include "multinomial_classifier.hh"
int argmax(std::vector<double> inp);
void MultinomialClassifier::trainOnDocument(Document &doc) {
    this->classCounter.addToCount(doc.realClass);
    this->model.updateFrequencies(doc,*(this->dictionary));
}
MultinomialClassifier::MultinomialClassifier(Dictionary* dictionary) {
    this->dictionary = dictionary;
}
std::string MultinomialClassifier::classify(Document &doc) {
    auto classes = classCounter.getVectorOfClasses();
    auto probabilities = std::vector<double>();
    for(auto klass:classes) {
        probabilities.push_back(getProbabilityOfClass(klass,doc));
    }
    return classes[argmax(probabilities)];
}
double MultinomialClassifier::getProbabilityOfClass(std::string klass,Document &doc) {
    return this->classCounter.relativeFrequency(klass) *
           this->model.getClassConditionalProbability(doc,klass);
}
int argmax(std::vector<double> inp) {
    int res = -1;
    double max = -1 * std::numeric_limits<double>::max();
    for( int i = 0; i < inp.size();i++) {
        if(inp[i] > max) {
            max = inp[i];
            res = i;     
        } 
    }
    return res;
}
