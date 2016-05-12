#include "document.hh"
#include <iostream>
std::string readSpaceSeparatedWord(std::stringstream& stream) {
    std::string s; std::getline(stream,s,' ');
    //This is just a special case for the spam corpus, because in that corpus,
    //guid and realClass are followed by TWO spaces instead of one
    if(s == "" && !stream.eof()) return readSpaceSeparatedWord(stream);
    return s;
}
Document Document::parseFromLine(std::string &str,Dictionary &dic) {
    auto res = Document();
    std::stringstream stream = std::stringstream(str);
    res.guid = readSpaceSeparatedWord(stream);
    res.realClass = readSpaceSeparatedWord(stream);

    while(true) {
        auto word = readSpaceSeparatedWord(stream);
        if(word == "") break;
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
