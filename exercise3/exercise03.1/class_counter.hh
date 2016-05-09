#ifndef CLASS_COUNTER_HH
#define CLASS_COUNTER_HH
#include <map>
#include <string>

class ClassCounter {
    public:
        void addToCount(std::string className);
        int getCount(std::string className);
        ClassCounter();
    private:
        std::map<std::string,int> counts;
};
#endif
