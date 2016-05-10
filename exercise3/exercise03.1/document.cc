#include "document.hh"
#include <iostream>
std::string readSpaceSeparatedWord(std::stringstream& stream) {
    std::string s; std::getline(stream,s,' ');return s;
}
Document Document::parseFromLine(std::string &str,Dictionary &dic) {
    auto res = Document();
    std::stringstream stream = std::stringstream(str);
    res.guid = readSpaceSeparatedWord(stream);
    //std::cout << "guid: " <<res.guid <<std::endl;
    res.realClass = readSpaceSeparatedWord(stream);
    //std::cout << "realClass: " <<res.realClass<<std::endl;
    while(true) {
        auto word = readSpaceSeparatedWord(stream);
        //Abort condition
        if(word == "") break;
        //std::cout << "word: " << word <<std::endl;
        auto countStr = readSpaceSeparatedWord(stream);
        //std::cout << "countStr: " << countStr <<std::endl;
        int count = std::stoi(countStr);
        int index = dic.insert(word);
        res.contentFrequencies[index] = count;
    } 
    return res;
}
Document::Document() {
    this->contentFrequencies = std::map<int,int>();
}
