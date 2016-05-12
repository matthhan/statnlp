#include "confusion_matrix.hh"

void ConfusionMatrix::insert(std::string realClass,std::string foundClass) {
    this->confusionCounts[std::make_pair(realClass,foundClass)]++;
    this->classesEncountered.insert(realClass);
}
std::string ConfusionMatrix::toString() {
    this->classesEncountered.erase("");
    std::string newline = "\n";
    std::string res = "true_class/classifier_output";
    //Make header row of table
    for(auto klass:this->classesEncountered) res = (res + "," + klass);
    res = res + ",REJECT" + newline;

    //fill table
    for(auto realClass:this->classesEncountered) {
        std::string nextline = realClass; 
        for(auto classifiedClass:this->classesEncountered) {
            int number = this->confusionCounts[std::make_pair(realClass,classifiedClass)];
            nextline = nextline + "," + std::to_string(number);
        }
        int number = this->confusionCounts[std::make_pair(realClass,"REJECT")];
        nextline = nextline + "," + std::to_string(number);
        nextline = nextline + newline;
        res = res + nextline;
    }
    return res;
}
ConfusionMatrix::ConfusionMatrix() {
    this->confusionCounts = std::map<std::pair<std::string,std::string>,int>();
    this->classesEncountered = std::set<std::string>();
}
