#include "document.hh"
Document Document::parseFromLine(std::string,Dictionary dic) {
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
