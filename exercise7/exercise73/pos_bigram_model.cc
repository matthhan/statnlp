#include "pos_bigram_model.hh"
PosBigramModel::PosBigramModel(Dictionary* posDictionary) {
    this->posDictionary = posDictionary;
}
void PosBigramModel::parseFromFile(string filename) {
    auto stream = ifstream(filename);

    string w = "\\1-grams:";
    while(readLine(stream) != w);

    this->readUnigramModel(stream);

    string w2 = "\\2-grams:";
    while(w2 != readLine(stream));

    this->readBigramModel(stream);
}
double PosBigramModel::probability(Pos first,Pos second) {
    //At beginning of sentence use unigram model
    if(first == -2) {
        return this->fallbackUnigramModel[second];
    }
    //otherwise try bigram model
    else {
        auto findAt = pair<Pos,Pos>(first,second);  
        //If bigram model yields result, use that
        double probabilityFound = this->bigramModel[findAt];
        if(probabilityFound != 0) {
            return probabilityFound;
        }
        //Otherwise use backoff weight
        double backoffWeight = this->backoffWeights[first];
        double unigramProbability = this->fallbackUnigramModel[second];
        return unigramProbability * backoffWeight;
    }
}
double PosBigramModel::logProbability(Pos first,Pos second) {
    return log(this->probability(first,second));
}

void PosBigramModel::readUnigramModel(ifstream& stream) { 
    string line;
    while((line = readLine(stream)) != "") {
        auto stringRead = splitAt(line,'\t');
        double prob = pow(10,stod(stringRead[0]));
        string unigram = stringRead[1];
        Pos pos = this->posDictionary->insert(unigram);
        double backoffWeight = pow(10,stod(stringRead[2]));
        this->fallbackUnigramModel[pos] = prob;
        this->backoffWeights[pos] = backoffWeight;
    }
}
void PosBigramModel::readBigramModel(ifstream& stream) { 
    string line;
    while((line = readLine(stream)) != "") {
        auto stringRead = splitAt(line,'\t');
        double prob = pow(10,stod(stringRead[0]));
        auto bigram = splitAt(stringRead[1],' ');
        string readString1 = bigram[0];
        string readString2 = bigram[1];
        Pos pos1 = this->posDictionary->insert(readString1);
        Pos pos2 = this->posDictionary->insert(readString2);
        auto insertAt = pair<Pos,Pos>(pos1,pos2);
        this->bigramModel[insertAt] = prob;
    }
}

