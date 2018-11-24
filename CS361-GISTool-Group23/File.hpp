#ifndef FILE_HPP
#define FILE_HPP
//#include "Support.hpp"
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>

//using std::ofstream;
//using std::ifstream;
//using std::vector;
using namespace std;

bool openFile(ifstream &, string);
bool openFile(ofstream &, string);
//vector<int> readFile(ifstream &, vector<int> &);
//void writeFile(ofstream &, vector<int>);
void closeFile(ifstream &);
void closeFile(ofstream &);
string formatFileName(string);
bool validFile(char*);

#endif // !FILE_HPP
