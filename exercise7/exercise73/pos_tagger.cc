#include "pos_tagger.hh"
//Some forward declarations
vector<double> addComponentWise(vector<double>& a, vector<double>& b);
int argmax(vector<double> inp);
double max(vector<double> inp);
vector<int> followBackpointer(vector<vector<int>>& backpointers,int startingIndex);
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
       finalSequence.push_back(bestChoice);
    }
    return finalSequence;
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
TagSequence PosTagger::tag(Sentence sentence) {
    this->refreshPossiblePoses();
    auto intermediateResults = vector<vector<double>>(sentence.size());
    auto backpointers = vector<vector<int>>(sentence.size());
    for(unsigned int i = 0; i < sentence.size();i++) {
        intermediateResults[i] = vector<double>(this->possiblePoses.size());
        backpointers[i] = vector<int>(this->possiblePoses.size());
        //First outer loop special case
        if(i == 0) {
            for(unsigned int j = 0; j < this->possiblePoses.size();j++) {
                intermediateResults[i][j] = this->membershipModel.logProbability(this->possiblePoses[j],sentence[i]);
            }
            continue;
        }
        //Normal case
        for(unsigned int j = 0; j < this->possiblePoses.size();j++) {
           double membershipLogProbability = this->membershipModel.logProbability(this->possiblePoses[j],sentence[i]); 

           auto combinationPossibilities = vector<double>(this->possiblePoses.size());
           for(unsigned int k = 0; k < this->possiblePoses.size();k++) {
               auto bigramProbability = this->posBigramModel.logProbability(this->possiblePoses[k],this->possiblePoses[j]);
               combinationPossibilities[k] = bigramProbability + 
                                             intermediateResults[i-1][k];
           }
           intermediateResults[i][j] = max(combinationPossibilities) + membershipLogProbability;
           backpointers[i][j] = argmax(combinationPossibilities);
        }
    } 
    auto bestEndingTagIndex = argmax(intermediateResults[sentence.size()-1]);
    auto bestTagSequenceIndices = followBackpointer(backpointers,bestEndingTagIndex);
    auto resultingTagSequence = vector<Pos>(bestTagSequenceIndices.size());
    for(unsigned int i = 0; i < bestTagSequenceIndices.size();i++) resultingTagSequence[i] = this->possiblePoses[bestTagSequenceIndices[i]];
    return resultingTagSequence;
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
double max(vector<double> inp) {
    double res = -1 * numeric_limits<double>::max();
    for(auto val: inp) {
        if(val > res) res = val;
    }
    return res;
}
vector<int> followBackpointer(vector<vector<int>>& backpointers,int startingIndex) {
    auto result = vector<int>();
    auto cur = startingIndex;
    result.push_back(cur);
    for(unsigned int i = (backpointers.size()-1); i != 0; i--) {
       cur = backpointers[i][cur];
       result.push_back(cur);
    }
    reverse(result.begin(),result.end());
    return result;
}

