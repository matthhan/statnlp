#ifndef DICTIONARY_HH
#define DICTIONARY_HH
#include "word.hh"
#include <vector>
#include <iostream>
#include <string>

class Dictionary {
    public:
        int insert(Word w);
        int getIndexForWord(Word w);
        Word getWordForIndex(int index);
        int contains(Word w);
        int size();
        Dictionary();
        void makeImmutable();
    private:
        static const size_t HASH_TABLE_SIZE = 10000000;
        std::vector<Word> content;
        std::hash<std::string> hash_fn;
        int hash(Word);
        int foundAt(Word w, int index);
        int probe(int index);
        bool immutable;
        int m_size;
};
#endif
