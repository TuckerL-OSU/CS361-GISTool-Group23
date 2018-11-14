#ifndef FILE_HPP
#define FILE_HPP
#include "Support.hpp"
#include <fstream>
#include <vector>

using std::ofstream;
using std::ifstream;
using std::vector;

bool openFile(ifstream &, string);
bool openFile(ofstream &, string);
vector<int> readFile(ifstream &, vector<int> &);
void writeFile(ofstream &, vector<int>);
void closeFile(ifstream &);
void closeFile(ofstream &);
string getFileName(string);


#endif // !FILE_HPP
