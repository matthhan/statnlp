#include "document.hh"
#include "class_counter.hh"
#include "dictionary.hh"
#include "multinomial_model.hh"
#include <cmath>
#include <limits>
#ifndef MULTINOMIAL_CLASSIFIER_HH
#define MULTINOMIAL_CLASSIFIER_HH


class MultinomialClassifier {
    public:
        void trainOnDocument(Document &doc);
        std::string classify(Document &doc);
        MultinomialClassifier();
        void enableSmoothing(Dictionary* dictionary);
    private:
        ClassCounter classCounter;
        MultinomialModel model;
        double getLogProbabilityOfClass(std::string klass,Document &doc);
};
#endif
