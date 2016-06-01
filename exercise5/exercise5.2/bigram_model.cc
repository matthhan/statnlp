#include "bigram_model.hh"
#include <iostream>
using std::cout;
using std::endl;

BigramModel::BigramModel(){}
BigramModel::BigramModel(string filePath,Dictionary& dict) {
    this->dict = &dict;
    cout << "Creating Bigram Model" << endl;
    this->lastReadWord = -1;
    this->fallbackUnigramModel = map<Word,pair<double,double>>();
    this->bigramModel = map<pair<Word,Word>,double>();
    auto stream = ifstream(filePath);

    cout << "Creating Unigram portion" << endl;
    string w = "\\1-grams:";
    while(readLine(stream) != w);
    this->readUnigramModel(stream);
    cout << "Creating Bigram portion" << endl;
    string w2 = "\\2-grams:";
    while(w2 != readLine(stream));
    this->readBigramModel(stream);
    cout << "Done creating Bigram Model" << endl;
}
double BigramModel::probability(Word s) {
    //At beginning of document use unigram model
    if(this->lastReadWord == -1) {
        this->lastReadWord = s;
        return this->fallbackUnigramModel[s].first;
    }
    //otherwise try bigram model
    else {
        auto findAt = pair<Word,Word>(this->lastReadWord,s);  
        //If bigram model yields result, use that
        double probabilityFound = this->bigramModel[findAt];
        if(probabilityFound != 0) {
            this->lastReadWord = s;
            return probabilityFound;
        }
        //Otherwise use backoff weight
        double backoffWeight = this->fallbackUnigramModel[lastReadWord].second;
        double unigramProbability = this->fallbackUnigramModel[s].first;
        this->lastReadWord = s;
        return unigramProbability * backoffWeight;
    }
}
double BigramModel::logProbability(Word s) {
    return log10(this->probability(s));
}
void BigramModel::readUnigramModel(ifstream& stream) { 
    string line;
    while((line = readLine(stream)) != "") {
        auto unigram = splitAt(line,'\t');
        double prob = pow(10,stod(unigram[0]));
        string stringRead = unigram[1];
        Word word = this->dict->insert(stringRead);
        if(word == this->dict->getWordForString("</s>")) unigram[2] = "1337";
        double backoffWeight = pow(10,stod(unigram[2]));

        cout << "inserting  at " << word << endl;
        auto p = make_pair(prob,backoffWeight);
        cout << "The pair (" << p.first << ", " << p.second << ")" << endl;
        cout << "Max size" << this->fallbackUnigramModel.max_size() << endl;
        cout << "size" << this->fallbackUnigramModel.size() << endl;
        cout << "Reading " << this->fallbackUnigramModel[word].first << endl;
        this->fallbackUnigramModel[word] = p;
        cout << "inserted" << endl;
    }
}
void BigramModel::readBigramModel(ifstream& stream) { 
    string line;
    while((line = readLine(stream)) != "") {
        auto bigram = splitAt(line,'\t');
        double prob = pow(10,stod(bigram[0]));
        string readString1 = bigram[1];
        string readString2 = bigram[1];
        Word word1 = this->dict->insert(readString1);
        Word word2 = this->dict->insert(readString2);
        auto insertAt = pair<Word,Word>(word1,word2);
        this->bigramModel[insertAt] = prob;
    }
}

