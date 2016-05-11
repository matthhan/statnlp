#include "occurence_counter.hh"
#include <utility>
#include <iostream>
#include <algorithm>
OccurenceCounter::OccurenceCounter() {
    this->counts = std::map<int,int>();
    this->eventsTotal = 0;
}
void OccurenceCounter::addToCount(int index) {
    this->addToCount(index,1);
}
void OccurenceCounter::addToCount(int index,int amount) {
    this->counts[index] += amount;
    this-> eventsTotal += amount;
}
int OccurenceCounter::getCount(int index) {return this->counts[index];}
//Plan: Dump the map into a vector of key-value-pairs.
//Than sort this vector by value element.
//Finally extract last n elements from this vector.
std::vector<std::pair<int,int>> OccurenceCounter::getNMostFrequent(int n) {
    //dump into vector
    auto pairVec = std::vector<std::pair<int,int>>(this->counts.size());
    for (auto it = this->counts.begin(); it != this->counts.end(); it++) {
        pairVec.push_back(std::pair<int,int>(it->first,it->second));
    }
    //Make function for sorting by second element of pair. (in descending order)
    struct sorter{
        bool operator()(std::pair<int,int> &left, std::pair<int,int> &right) { 
            return left.second > right.second;   
        }
    };
    //sort
    std::sort(pairVec.begin(),pairVec.end(),sorter());
    //Extract last n indices
    auto result = std::vector<std::pair<int,int>>(n);
    auto it = pairVec.begin();
    for(int i = 0; i < n;i++) {
       result.push_back(*it);
       it++;
    }
    return result;
}
double OccurenceCounter::getProbability(int word) {
    return ((double)this->getCount(word)/(double)this->eventsTotal);
}

