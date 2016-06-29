#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <map>
#include <cstdlib>
#include <ctype.h>
#include <unistd.h>
#include "file_io.hh"

using std::endl;
using std::cout;
using std::string;
using std::map;
using std::ifstream;
using std::min;

void validateParams(map<string,string>& params);
map<string,string> parseCLIParams(int argc,char* argv[]);
void printUsage();
//calculates WER
typedef vector<string> Sentence ;
double wer(Sentence reference,Sentence hypothesis);
//Finds the best alignment path for WER
vector<vector<int>> findPaths(Sentence reference,Sentence hypothesis);
//returns the smallest of the variables
int min3(int a,int b, int c);
//returns 1 if a is smallest, 2 if b is smallest, 3 if c is smallest
int argmin3(int a,int b, int c);
int main(int argc, char* argv[]);

int main(int argc, char* argv[]){
    auto params = parseCLIParams(argc,argv);
    validateParams(params);
    auto referencePath = params["referencePath"];
    auto hypothesisPath = params["hypothesisPath"];
    auto positionIndependent = params["positionIndependent"] == "true";
    auto referenceFile = ifstream(referencePath);
    auto hypothesisFile = ifstream(hypothesisPath);

    int i = 0;
    double sum = 0;
    while(canReadMore(referenceFile) && canReadMore(hypothesisFile)) {
       auto hypothesisSentence = splitAt(readLine(hypothesisFile),' ');
       auto referenceSentence = splitAt(readLine(referenceFile),' ');
       //Calculates the optimal Paths and minimum Distances
       double weri = wer(referenceSentence,hypothesisSentence);
       cout << "The WER for Sentence " << i << " is " << weri << "." << endl;
       sum += weri;
       i++;
    }
    cout << "The average WER of all sentences is " << sum/(double)(i+1) << "." << endl;
    return 0;
}


double wer (Sentence reference, Sentence hypothesis) {
       auto d = findPaths(reference,hypothesis);
       double wer = (double)d[d.size()-1][d[d.size()-1].size()-1]
                      /(double)reference.size();
       return wer;
}
vector<vector<int>> findPaths(Sentence reference,Sentence hypothesis) {
    //minDists[i][j] contains the minimal path to align the WordLists up to i and j
    auto minDists = vector<vector<int>>();
    for(int i = 0;i < hypothesis.size();i++) {
        minDists.push_back(vector<int>());
        for(int j = 0;j < reference.size();j++) {
            minDists[i].push_back(0);
        }
    }
    //In these nested for-loops, the minimal distance and the partially optimal paths are calculated
    for(int i = 0;i < minDists.size();i++) {//columns, then rows
        for(int j = 0;j < minDists[i].size();j++) {
           int neq;
           if(hypothesis[i] == reference[j]) neq = 0;
           else neq = 1;

           //corner case where we are in the bottom left corner
           if(i == 0 && j == 0)  minDists[i][j] = neq;
           //corner case where we are in the leftmost column
           else if(i == 0) minDists[i][j] = neq + minDists[i][j-1];
           //corner case where we are in the lowest row
           else if(j == 0) minDists[i][j] = neq + minDists[i-1][j];
           //The normal case
           else{
               minDists[i][j] = neq + min3(minDists[i-1][j-1],
                                          minDists[i-1][j], 
                                          minDists[i][j-1]); 
           }
        }
    }
    return minDists;
}

int min3(int a,int b, int c) {
    return min(a,min(b,c));
}

int argmin3(int a,int b,int c) {
    int m = min3(a,b,c);
    if(m == a) return 1;
    else if(m == b) return 2;
    else return 3;
}


map<string,string> parseCLIParams(int argc,char* argv[]) {
    auto params = map<string,string>();
    int c;
    while((c = getopt(argc,argv,"r:h:p")) != -1) {
        switch (c) {
           case 'r':
               params["referencePath"] = optarg;
               break;
           case 'h':
               params["hypothesisPath"] = optarg;
               break;
           case 'p':
               params["positionIndependent"] = "true";
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
void validateParams(map<string,string>& params) {
    if(params["referencePath"] == "" ||
       params["hypothesisPath"] == "") {
       printUsage();
       exit(1);
    }
}
void printUsage() {
    cout << " usage: <program name> " << 
	        "-r <reference-sentences-file> -h <hypothesis-sentences-file> -p" << endl <<
            "-p flag turns on position independent word error rate" << endl;
    exit(1);
}

