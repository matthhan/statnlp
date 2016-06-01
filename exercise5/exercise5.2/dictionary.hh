#ifndef DICTIONARY_HH
#define DICTIONARY_HH
#include "word.hh"
#include <vector>
#include <iostream>
#include <string>
using std::vector;
using std::string;
using std::hash;

class Dictionary {
    public:
        Word insert(string w);
        Word getWordForString(string w);
        string getStringForWord(Word index);
        bool contains(string w);
        int size();
        Dictionary();
        void makeImmutable();
    private:
        static const size_t HASH_TABLE_SIZE = 10000000;
        vector<string> content;
        hash<string> hash_fn;
        int hash(string);
        int foundAt(string w, Word index);
        int probe(int index);
        bool immutable;
        int m_size;
};
#endif
