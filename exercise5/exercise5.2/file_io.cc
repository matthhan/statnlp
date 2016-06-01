#include "file_io.hh"

bool canReadMore(ifstream& stream) {
    return !stream.eof();
}
string readWord(std::ifstream& stream) {
    string s;getline(stream,s,' '); return s;
}
string readLine(std::ifstream& stream) {
    string s;getline(stream,s); return s;
}
vector<string> splitAt(string s,char delim) {
    auto res = vector<string>();
    auto stream = stringstream(s);
    while(!stream.eof()) {
        string w;
        getline(stream,w,delim);
        res.push_back(w);
    }
    return res;
}

