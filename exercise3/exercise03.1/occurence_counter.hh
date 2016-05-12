#ifndef OCCURENCE_COUNTER_HH
#define OCCURENCE_COUNTER_HH
#include <map>
#include <vector>
#include <utility>
#include <algorithm>

class OccurenceCounter {
    public:
        void addToCount(int index);
        void addToCount(int index,int amount);
        int getCount(int index);
        double getProbability(int word);
        double getSmoothedProbability(int word,int dictionary_size);
        std::vector<std::pair<int,int>> getNMostFrequent(int n);
        OccurenceCounter();
    private:
        std::map<int,int> counts;
        unsigned int eventsTotal;
};
#endif
