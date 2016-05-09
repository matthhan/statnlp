#include "dictionary.hh"
#include "document.hh"
#ifndef MULTINOMIAL_MODEL_HH
#define MULTINOMIAL_MODEL_HH

class MultinomialModel {
    public:
        void updateFrequencies(Document doc,Dictionary dic);
        double getClassConditionalProbability();
    private:
};
#endif
