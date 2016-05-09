#include <vector>
#include <string>
#include <utility>
#include "dictionary.hh"
#ifndef DOCUMENT_HH
#define DOCUMENT_HH
class Document {
    public:
        static Document parseFromLine(std::string,Dictionary dic);
        std::vector<std::pair<int,int>> contentFrequencies;
        std::string guid;
        std::string realClass; 
    private:
        Document(); 
};
#endif
