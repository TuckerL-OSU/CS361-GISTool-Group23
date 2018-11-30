#ifndef SUPPORT_HPP
#define SUPPORT_HPP

#include <iostream>
#include <string>
#include <limits>
#include <limits.h>
#include <locale>
#include <sstream>
#include <cstdlib>
#include <string.h>

using namespace std;
//using std::string;
//using std::cout;
//using std::cin;
//using std::endl;
//using std::getline;
//using std::numeric_limits;
//using std::streamsize;
//using std::stringstream;

int getInteger(string, int, int);
string getStringInput();
char** parseInput(string, int);

char* getCharInput();
int RNG(int, int);
int playAgain();

#endif // !SUPPORT_HPP