#include "multinomial_classifier.hh"
void MultinomialClassifier::trainOnDocument(Document &doc) {
    this->classCounter.addToCount(doc.realClass);
    this->model.updateFrequencies(doc,*(this->dictionary));
}
MultinomialClassifier::MultinomialClassifier(Dictionary* dictionary) {
    this->dictionary = dictionary;
}
std::string MultinomialClassifier::classify(Document &doc) {
    //TODO:implement
    return "";
}


