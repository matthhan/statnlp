#ifndef OCCURENCE_COUNTER_HH
#define OCCURENCE_COUNTER_HH
#include <map>
#include <vector>

class OccurenceCounter {
    public:
        void addToCount(int index);
        int getCount(int index);
        std::vector<int> getNMostFrequent(int n);
        OccurenceCounter();
    private:
        std::map<int,int> counts;
};
#endif
