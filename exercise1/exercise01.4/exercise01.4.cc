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
    std::ifstream input = std::ifstream("alice_preprocessed.txt");
    Dictionary dic = Dictionary();
    OccurenceCounter counter = OccurenceCounter();
    while(canReadMore(input)) {
        Word w = readWord(input);
        int insertedAt = dic.insert(w);
        counter.addToCount(insertedAt);
    }
    input.close();
    std::cout << counter.getCount(dic.getIndexForWord("alice")) << std::endl;
    counter.getNMostFrequent(10);
}
