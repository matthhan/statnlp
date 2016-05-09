#ifndef OCCURENCE_COUNTER_HH
#define OCCURENCE_COUNTER_HH
#include <map>
#include <vector>
#include <utility>

class OccurenceCounter {
    public:
        void addToCount(int index);
        int getCount(int index);
        std::vector<std::pair<int,int>> getNMostFrequent(int n);
        OccurenceCounter();
    private:
        std::map<int,int> counts;
};
#endif
