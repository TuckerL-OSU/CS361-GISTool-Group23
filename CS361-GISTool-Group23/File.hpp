#ifndef FILE_HPP
#define FILE_HPP
#include "Support.hpp"
#include <fstream>
#include <vector>

//using std::ofstream;
//using std::ifstream;
//using std::vector;

bool openFile(ifstream &, string);
bool openFile(ofstream &, string);
void closeFile(ifstream &);
void closeFile(ofstream &);
string formatFileName(string);
bool validFile(char*);
char** getNewFiles(char**);

#endif // !FILE_HPP
