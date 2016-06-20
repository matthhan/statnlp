#include "pos_tagger.hh"
PosTagger::PosTagger(Dictionary* wordDictionary,Dictionary* posDictionary) : 
    membershipModel(wordDictionary), 
    posBigramModel(posDictionary) {
    this->posDictionary = posDictionary;
}
void PosTagger::trainOn(AnnotatedSentence s) {
    this->membershipModel.trainOn(s);
    this->possiblePosesDirty = true;
}
void PosTagger::parsePosBigramModel(string filename){
    this->posBigramModel.parseFromFile(filename);
    possiblePosesDirty = true;
}
//Some forward declarations
vector<double> addComponentWise(vector<double>& a, vector<double>& b);
int argmax(vector<double> inp);
void printVector(vector<double> vec);
TagSequence PosTagger::tag_greedy(Sentence sentence) {
    this->refreshPossiblePoses();
    vector<Pos> finalSequence = vector<Pos>();

    if(sentence.size() == 0) return finalSequence;

    Word first = sentence[0];
    //First word is just the word with the highest membership probability
    finalSequence.push_back(this->possiblePoses[argmax(this->getMembershipLogProbabilities(first))]);
    if(sentence.size() == 1) return finalSequence;
    for(unsigned int i = 1; i < sentence.size(); i++) {
       auto membershipProbabilities =  this->getMembershipLogProbabilities(sentence[i]); 
       auto bigramProbabilities = this->getBigramLogProbabilities(finalSequence[i-1]);
       auto scores = addComponentWise(membershipProbabilities,bigramProbabilities);
       auto bestChoice = this->possiblePoses[argmax(scores)];
       //printVector(membershipProbabilities);
       finalSequence.push_back(bestChoice);
    }
    return finalSequence;
}
TagSequence PosTagger::tag(Sentence sentence) {
    return TagSequence();
}
vector<double> PosTagger::getMembershipLogProbabilities(Word w) {
    auto res = vector<double>();
    for(auto pos:this->possiblePoses) res.push_back(this->membershipModel.logProbability(pos,w));
    return res;
}
vector<double> PosTagger::getBigramLogProbabilities(Pos first)  {
    auto res = vector<double>(this->possiblePoses.size());
    for(auto pos:this->possiblePoses) res.push_back(this->posBigramModel.logProbability(first,pos));
    return res;
}
vector<double> addComponentWise(vector<double>& a, vector<double>& b) {
    vector<double> res = vector<double>(a.size());
    for(unsigned int i= 0; i < a.size();i++) res[i] = a[i] + b[i];
    return res;
}
void PosTagger::refreshPossiblePoses() {
    if(this->possiblePosesDirty) {
        this->possiblePoses = this->posDictionary->getAllWords();
    } 
    this->possiblePosesDirty = false;
}
int argmax(vector<double> inp) {
    int res = -1;
    double max = -1 * numeric_limits<double>::max();
    for(unsigned int i = 0; i < inp.size();i++) {
        if(inp[i] > max) {
            max = inp[i];
            res = i;     
        } 
    }
    return res;
}
