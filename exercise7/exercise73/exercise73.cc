#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

#include <cstdlib>
#include <ctype.h>
#include <unistd.h>

#include "dictionary.hh"
#include "pos_tagger.hh"
#include "file_io.hh"

using std::endl;
using std::cout;
using std::string;
using std::map;
using std::ifstream;
//Forward declarations
void printUsage();
void validateParams(map<string,string>& params);
map<string,string> parseCLIParams(int argc,char* argv[]);
int findNumberOfMatches(TagSequence a, TagSequence b);

int main(int argc, char* argv[]) {
    //Parameter handling
    auto params = parseCLIParams(argc,argv);
    validateParams(params);
    string trainSentencesPath = params["trainSentencesPath"];
    string trainTagsPath = params["trainTagsPath"];
    string posBigramModelPath = params["posBigramModelPath"];
    string testSentencesPath = params["testSentencesPath"];
    string testTagsPath = params["testTagsPath"];
    bool greedy = false;
    if(params["greedy"] == "true") greedy = true;

    auto wordDictionary = Dictionary();
    auto posDictionary = Dictionary();

    auto tagger = PosTagger(&wordDictionary,&posDictionary);
    
    tagger.parsePosBigramModel(posBigramModelPath);
    auto trainSentencesFile = ifstream(trainSentencesPath);
    auto trainTagsFile = ifstream(trainTagsPath);
    
    while(canReadMore(trainSentencesFile)) {
        Sentence sentence = wordDictionary.insertMany(splitAt(readLine(trainSentencesFile),' '));
        TagSequence tagSequence = posDictionary.insertMany(splitAt(readLine(trainTagsFile),' '));
        AnnotatedSentence as = makeAnnotatedSentence(sentence,tagSequence);
        tagger.trainOn(as);
    }
    trainSentencesFile.close();
    trainTagsFile.close();
    wordDictionary.makeImmutable();


    //Test the Tagger
    auto testSentencesFile = ifstream(testSentencesPath);
    auto testTagsFile = ifstream(testTagsPath);

    int numberCorrectlyTagged = 0;
    int numberTried = 0;
    int i = 0;
    cout << "Testing . . ." << std::flush;
    while(canReadMore(testSentencesFile)) {
        Sentence s = wordDictionary.insertMany(splitAt(readLine(testSentencesFile),' '));
        TagSequence t = posDictionary.insertMany(splitAt(readLine(testTagsFile),' '));
        TagSequence found;
        if(!greedy) found = tagger.tag(s); 
        else found = tagger.tag_greedy(s);
        numberCorrectlyTagged += findNumberOfMatches(found,t);
        numberTried += t.size();
        i++;
        if(i % 1000 == 0) cout << i << ", " << std::flush;
    }
    cout << endl;

    testSentencesFile.close();
    testTagsFile.close();
    double errorRate = 1- ((double)numberCorrectlyTagged/(double)numberTried);
    cout << "Error Rate: " << errorRate << endl;
}

int findNumberOfMatches(TagSequence a, TagSequence b) {
    int matches = 0;
    for(unsigned int i = 0; i < a.size();i++) {
        if(a[i] == b[i]) matches++;
    } 
    return matches;
}

map<string,string> parseCLIParams(int argc,char* argv[]) {
    auto params = map<string,string>();
    int c;
    while((c = getopt(argc,argv,"t:u:v:w:x:g")) != -1) {
        switch (c) {
           case 't':
               params["trainSentencesPath"] = optarg;
               break;
           case 'u':
               params["trainTagsPath"] = optarg;
               break;
           case 'v':
               params["posBigramModelPath"] = optarg;
               break;
           case 'w':
               params["testSentencesPath"] = optarg;
               break;
           case 'x':
               params["testTagsPath"] = optarg;
               break;
           case 'g':
               params["greedy"] = "true";
               break;
           case '?':
               printUsage();
               exit(1);
           default:
               printUsage();
               exit(1);
        } 
    }
    return params;
}
void printUsage() {
    cout << "Usage:" << endl << 
       "<program> -t <file-with-training-sentences> -u <file-with-training-tag-sequences>" << endl << 
       "-v <file-with-pos-bigram-model>" << endl <<
       "-w <file-with-test-sentences> -x <file-with-test-tag-sequences>" << endl;
}
void validateParams(map<string,string>& params) {
    if(params["trainSentencesPath"] == "" ||
       params["trainTagsPath"] == "" ||
       params["posBigramModelPath"] == "" ||
       params["testSentencesPath"]== "" ||
       params["testTagsPath"] == "") {
       printUsage();
       exit(1);
    }
}

