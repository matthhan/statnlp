#include "multinomial_model.hh"
double multinomialCoefficient(Document &doc);
unsigned long long factorial(int  n);
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
double MultinomialModel::getClassConditionalProbability(Document &doc,
        std::string klass) {
    //TODO gets too close to 0 too fast
    //Use the model for the class that we are interested in
    //auto& classSpecificModel = ;
    double countVectorProbability = 1;
    //compute the probability for a document that contains these words
    for(auto tupl:doc.contentFrequencies) {
        int word = tupl.first;
        int count = tupl.second;
        std::cout << countVectorProbability << std::endl;
        countVectorProbability *= 
            std::pow(this->classConditionalProbabilities[klass].getProbability(word),count);
    }
    //multiply with multinomial coefficient
    //return multinomialCoefficient(doc) * countVectorProbability;
    return countVectorProbability;
}
double multinomialCoefficient(Document &doc) {
    //TODO: This part is kinda buggy, because the numbers 
    //for multinomial coefficients just become too big after a while
    int documentLength = 0;
    auto frequencies = std::vector<long long>();
    for(auto tupl:doc.contentFrequencies) {
        long long frequency = tupl.second;
        documentLength += frequency; 
        frequencies.push_back(frequency);
    }
    long double productOfFrequencyFactorials = 1;
    for(long long frequency:frequencies) {
        //std::cout << productOfFrequencyFactorials << std::endl;
        //std::cout<< "freq: " << frequency << ":"<< factorial(frequency) << std::endl;
        productOfFrequencyFactorials *= (long double)factorial(frequency);
    }
    return factorial(documentLength)/productOfFrequencyFactorials;
}
unsigned long long factorial(int n) {
    if(n==0) return 1;
    else return n*factorial(n-1);
}
