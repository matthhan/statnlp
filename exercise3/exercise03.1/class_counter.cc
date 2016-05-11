#include "class_counter.hh"
#include <iostream>
void ClassCounter::addToCount(std::string className) {
    this->counts[className]++;
    this->totalCount++;
}
int ClassCounter::getCount(std::string className) {
    return this->counts[className];
}
ClassCounter::ClassCounter() {
    this->counts = std::map<std::string,int>();
    this->totalCount = 0;
}
double ClassCounter::relativeFrequency(std::string className) {
    return (double)this->getCount(className)/(double)this->totalCount;
}
std::vector<std::string> ClassCounter::getVectorOfClasses() {
    auto res = std::vector<std::string>();
    for(auto key:this->counts) {
        if(key.first == "") continue;
        res.push_back(key.first);
    }
    return res;
}
