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
}
double MultinomialModel::getClassConditionalLogProbability(Document &doc,
        std::string klass) {
    double countVectorLogProbability = 0;
    //compute the log probability for a document that contains these words
    for(auto tupl:doc.contentFrequencies) {
        int word = tupl.first;
        int count = tupl.second;
        countVectorLogProbability += 
            std::log(this->classConditionalProbabilities[klass].getProbability(word))*count;
    }
    return countVectorLogProbability; //+ logMultinomialCoefficient(doc);
}
//apparently multinomial coefficient not necessary
/*double logFactorial(int n) {
    auto res = 0;
    for(int i = 0; i < n;i++) res += std::log(n);
    return res;
}
double logMultinomialCoefficient(Document &doc) {
    int documentLength = 0;
    auto frequencies = std::vector<int>();
    for(auto tupl:doc.contentFrequencies) {
        int frequency = tupl.second;
        documentLength += frequency; 
        frequencies.push_back(frequency);
    }
    double sumOfFrequencyLogFactorials = 0;
    for(int frequency:frequencies) {
        sumOfFrequencyLogFactorials += logFactorial(frequency);
    }
    return logFactorial(documentLength)-sumOfFrequencyLogFactorials;
}*/
