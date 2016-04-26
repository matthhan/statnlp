#include "occurence_counter.hh"
#include <utility>
#include <iostream>
#include <algorithm>
OccurenceCounter::OccurenceCounter() {this->counts = std::map<int,int>();}
void OccurenceCounter::addToCount(int index) {this->counts[index]++;}
int OccurenceCounter::getCount(int index) {return this->counts[index];}
//Plan: Dump the map into a vector of key-value-pairs.
//Than sort this vector by value element.
//Finally extract last n elements from this vector.
std::vector<int> OccurenceCounter::getNMostFrequent(int n) {
    //dump into vector
    auto pairVec = std::vector<std::pair<int,int>>(this->counts.size());
    for (auto it = this->counts.begin(); it != this->counts.end(); it++) {
        pairVec.push_back(std::pair<int,int>(it->first,it->second));
    }
    //Make function for sorting by second element of pair.
    struct sorter{
        bool operator()(std::pair<int,int> &left, std::pair<int,int> &right) { 
            return left.second < right.second;   
        }
    };
    //sort
    std::sort(pairVec.begin(),pairVec.end(),sorter());

    //Extract last n indices
    auto result = std::vector<int>(n);
    auto it = pairVec.end();
    for(int i = 0; i < n;i++) {
       result.push_back(it->first);
       it++;
    }
    return result;
}
