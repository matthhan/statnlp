#include "document.hh"
#include <sstream>

std::string readSpaceSeparatedWord(std::stringstream& stream) {
    std::string s; std::getline(stream,s,' ');return s;
}
Document Document::parseFromLine(std::string str,Dictionary dic) {
    auto res = Document();
    std::stringstream stream = std::stringstream(str);
    res.guid = readSpaceSeparatedWord(stream);
    res.realClass = readSpaceSeparatedWord(stream);
    while(stream) {
        auto word = readSpaceSeparatedWord(stream);
        auto countStr = readSpaceSeparatedWord(stream);
        int count = std::stoi(countStr);
        int index = dic.insert(word);
        res.contentFrequencies[index] = count;
    } 
    return res;
}
Document::Document() {
    this->contentFrequencies = std::map<int,int>();
}
