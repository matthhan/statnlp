#include "class_counter.hh"
void ClassCounter::addToCount(std::string className) {
    this->counts[className];
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
    return this->getCount(className)/this->totalCount;
}
