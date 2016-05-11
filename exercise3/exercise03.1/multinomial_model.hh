#include "dictionary.hh"
#include "document.hh"
#include "occurence_counter.hh"
#include <map>
#include <string>
#include <cmath>
#ifndef MULTINOMIAL_MODEL_HH
#define MULTINOMIAL_MODEL_HH

class MultinomialModel {
    public:
        void updateFrequencies(Document &doc);
        double getClassConditionalLogProbability(Document &doc,std::string klass);
        void enableSmoothing(Dictionary* dictionary);
        MultinomialModel();
    private:
        std::map<std::string,OccurenceCounter> classConditionalProbabilities;
        bool smoothed;
        Dictionary* dictionary;
};
#endif
