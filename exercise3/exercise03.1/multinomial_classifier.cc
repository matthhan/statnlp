#include "multinomial_classifier.hh"
#include <iostream>
#include <limits>
int argmax(std::vector<double> inp);
void MultinomialClassifier::trainOnDocument(Document &doc) {
    this->classCounter.addToCount(doc.realClass);
    this->model.updateFrequencies(doc);
}
MultinomialClassifier::MultinomialClassifier() {}
std::string MultinomialClassifier::classify(Document &doc) {
    auto classes = classCounter.getVectorOfClasses();
    auto probabilities = std::vector<double>();
    for(auto klass:classes) {
        probabilities.push_back(getLogProbabilityOfClass(klass,doc));
    }
    int position = argmax(probabilities);
    if(position == -1) return "REJECT";
    else return classes[argmax(probabilities)];
}
double MultinomialClassifier::getLogProbabilityOfClass(std::string klass,Document &doc) {
    double res = std::log(this->classCounter.relativeFrequency(klass)) +
           this->model.getClassConditionalLogProbability(doc,klass);
    return res;
}
int argmax(std::vector<double> inp) {
    int res = -1;
    double max = -1 * std::numeric_limits<double>::max();
    for(unsigned int i = 0; i < inp.size();i++) {
        if(inp[i] > max) {
            max = inp[i];
            res = i;     
        } 
    }
    return res;
}
