#include "dictionary.hh"
Dictionary::Dictionary(void) {
   this->content = vector<string>(this->HASH_TABLE_SIZE);
   this->immutable = false;
   this->m_size = 0;
}
string Dictionary::getStringForWord(Word index) {
    return this->content[index];
}
int Dictionary::insert(string w) {
    if(this->immutable) return this->getWordForString(w);
    int insertAt = this->hash(w);
    //Insert word
    if(this->content[insertAt].empty()) {this->content[insertAt] = w;this->m_size++;return insertAt;}
    //Word is already in HashTable
    else if(this->content[insertAt] == w) return insertAt;
    //Need to handle collision
    else {
       int originalHashValue = insertAt;
       while(1) {
           insertAt = probe(insertAt);
           int res = foundAt(w,insertAt);
           if(res == -1) {
                this->content[insertAt] = w;
                this->m_size++;
                return insertAt;
           } else if(res == insertAt) return insertAt;
           if(insertAt == originalHashValue) {
                std::cout << 
                    "Error in Dictionary::insert: Tried to insert value into Full HashTable"
                    << std::endl;
                return-1;
           }
       } 
    }
}
int Dictionary::getWordForString(string w) {
    int shouldBeAt = hash(w);
    int returnValue = foundAt(w,shouldBeAt);
    if(returnValue == shouldBeAt) return shouldBeAt;
    else if(returnValue == -1) return -1;
    else {
        int originalHashValue = shouldBeAt;
        while(1) {
            shouldBeAt = probe(shouldBeAt);
            int res = foundAt(w,shouldBeAt);
            if(res == shouldBeAt) return shouldBeAt;
            else if(res == -1) return -1;
            else if(shouldBeAt == originalHashValue)  return -2;
        }
    }
}
int Dictionary::hash(string w) {
    return this->hash_fn(w) % this->HASH_TABLE_SIZE;
}
int Dictionary::foundAt(string w, int index) {
    //Found the word at the index
    if(this->content[index] == w) return index;
    //Found that the index is still free
    else if(this->content[index].empty()) return -1;
    //Found different Word
    else return -2;
}
int Dictionary::probe(int index) {
    return (index + 1) % this->HASH_TABLE_SIZE;
}
void Dictionary::makeImmutable() {
    this->immutable = true;
}
int Dictionary::size() {
    return this->m_size;
}
vector<Word> Dictionary::insertMany(vector<string> sequence) {
    auto result = vector<Word>();
    for(auto token:sequence) {
        result.push_back(this->insert(token));
    }
    return result;
}
vector<Word> Dictionary::getAllWords() {
    vector<Word> res = vector<Word>();
    for(auto w:this->content) {
        if(w != "") res.push_back(this->getWordForString(w));
    }
    return res;
}
