#ifndef CONFUSION_MATRIX_HH
#define CONFUSION_MATRIX_HH
#include <map>
#include <set>
#include <string>

class ConfusionMatrix {

    public:
        void insert(std::string realClass,std::string foundClass);
        std::string toString();
        ConfusionMatrix();
    private:
        std::map<std::pair<std::string,std::string>,int> confusionCounts;
        std::set<std::string> classesEncountered;
};
#endif
