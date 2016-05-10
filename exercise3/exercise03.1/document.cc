#include "document.hh"
#include <sstring>
Document Document::parseFromLine(std::string str,Dictionary dic) {
    auto res = Document();
    std::stringstream stream = std::stringstream(str);
    
    //TODO implement
    //Ignore First word
    //Then real class
    //Then occurence counts
    //Read Words and count occurences
    return Document();
}
Document::Document() {
    this->contentFrequencies = std::vector<std::pair<int,int>>();
}
