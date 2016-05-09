#ifndef CLASS_COUNTER_HH
#define CLASS_COUNTER_HH
#include <map>
#include <vector>
#include <string>

class ClassCounter {
    public:
        void addToCount(std::string className);
        ClassCounter();
        double relativeFrequency(std::string className);
        std::vector<std::string> getVectorOfClasses();
    private:
        int getCount(std::string className);
        std::map<std::string,int> counts;
        int totalCount;
};
#endif
