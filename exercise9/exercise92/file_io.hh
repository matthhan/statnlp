#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using std::vector;
using std::ifstream;
using std::string;
using std::stringstream;
bool canReadMore(ifstream& stream);
string readWord(ifstream& stream);
string readLine(ifstream& stream);
vector<string> splitAt(string s,char delim);

