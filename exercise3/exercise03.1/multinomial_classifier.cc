#include "multinomial_classifier.hh"
#include <iostream>
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
        probabilities.push_back(getProbabilityOfClass(klass,doc));
    }
    //for(auto prob: probabilities) {std::cout << prob<<std::flush;}
    return classes[argmax(probabilities)];
}
double MultinomialClassifier::getProbabilityOfClass(std::string klass,Document &doc) {
    //second one has weird values of these are relatively close to 0
    double res = this->classCounter.relativeFrequency(klass) *
           this->model.getClassConditionalProbability(doc,klass);
    //std::cout << res <<std::endl;
    return res;
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
