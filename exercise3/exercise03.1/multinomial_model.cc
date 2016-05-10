#include "multinomial_model.hh"
double multinomialCoefficient(Document &doc);
int factorial(int n);
void MultinomialModel::updateFrequencies(Document &doc,Dictionary &dic) {
    std::string klass = doc.realClass;
    auto ma = this->classConditionalProbabilities;
    //Create the counter for this class if it does not exist yet
    if(ma.find(klass) == ma.end()) ma[klass] = OccurenceCounter();
    //add the word frequencies to the model
    for(auto indexFrequencyTuple:doc.contentFrequencies) {
        int index = indexFrequencyTuple.first;
        int frequency = indexFrequencyTuple.second;
        ma[klass].addToCount(index,frequency);
    }
}

MultinomialModel::MultinomialModel() {
    this->classConditionalProbabilities = 
        std::map<std::string,OccurenceCounter>();
}
double MultinomialModel::getClassConditionalProbability(Document &doc,
        std::string klass) {
    //Use the model for the class that we are interested in
    auto classSpecificModel = this->classConditionalProbabilities[klass];
    int countVectorProbability = 1;
    //compute the probability for a document that contains these words
    for(auto tupl:doc.contentFrequencies) {
        int word = tupl.first;
        int count = tupl.second;
        countVectorProbability *= 
            std::pow(classSpecificModel.getProbability(word),count);
    }
    //multiply with multinomial coefficient
    return multinomialCoefficient(doc) * countVectorProbability;
}
double multinomialCoefficient(Document &doc) {
    int documentLength = 0;
    auto frequencies = std::vector<int>();
    for(auto tupl:doc.contentFrequencies) {
        int frequency = tupl.second;
        documentLength += frequency; 
        frequencies.push_back(frequency);
    }
    int productOfFrequencyFactorials = 1;
    for(int frequency:frequencies) {
        productOfFrequencyFactorials *= factorial(frequency);
    }
    return factorial(documentLength)/productOfFrequencyFactorials;
}
int factorial(int n) {
    if(n==0) return 1;
    else return n*factorial(n-1);
}
