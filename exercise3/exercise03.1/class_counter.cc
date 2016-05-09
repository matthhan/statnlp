#include "class_counter.hh"
void ClassCounter::addToCount(std::string className) {
    this->counts[className];
}
int ClassCounter::getCount(std::string className) {
    return this->counts[className];
}
ClassCounter::ClassCounter() {
    this->counts = std::map<std::string,int>();
}
