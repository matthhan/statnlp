#include <iostream>
#include "word.hh"
#include "dictionary.hh"
#include "occurence_counter.hh"
#include <vector>
#include <fstream>
#include <string>
//Currently just uses \n as delimiter. Maybe write more sophisticated Version?
Word readWord(std::ifstream& stream) {std::string s;std::getline(stream,s); return s;}
bool canReadMore(std::ifstream& stream) {return !stream.eof();}
int main() {
    auto input = std::ifstream("alice_preprocessed.txt");
    auto dic = Dictionary();
    auto counter = OccurenceCounter();
    auto textAsIndices = std::vector<int>();
    while(canReadMore(input)) {
        Word w = readWord(input);
        int insertedAt = dic.insert(w);
        counter.addToCount(insertedAt);
        textAsIndices.push_back(insertedAt);
    }
    input.close();
    auto frequentPairs = counter.getNMostFrequent(1000);
    for(auto index:textAsIndices) {
        bool inMostFrequentWords = false;
        for(auto pair:frequentPairs) {
            if(index == pair.first) {inMostFrequentWords =true;break;}
        }
        if(inMostFrequentWords) std::cout << dic.getWordForIndex(index) << " ";
        else std::cout << "<UNK>";
    }
}
