#include "dictionary.hh"
#include "document.hh"
#include "occurence_counter.hh"
#include <map>
#include <cmath>
#ifndef MULTINOMIAL_MODEL_HH
#define MULTINOMIAL_MODEL_HH

class MultinomialModel {
    public:
        void updateFrequencies(Document &doc);
        double getClassConditionalProbability(Document &doc,std::string klass);
        MultinomialModel();
    private:
        std::map<std::string,OccurenceCounter> classConditionalProbabilities;
};
#endif
