#include "document.hh"
#include "class_counter.hh"
#include "dictionary.hh"
#include "multinomial_model.hh"
#ifndef MULTINOMIAL_CLASSIFIER_HH
#define MULTINOMIAL_CLASSIFIER_HH


class MultinomialClassifier {
    public:
        void trainOnDocument(Document doc);
        std::string classify(Document doc);
        MultinomialClassifier(Dictionary* dic);
    private:
        ClassCounter classCounter;
        MultinomialModel model;
        Dictionary* dictionary;
};
#endif
