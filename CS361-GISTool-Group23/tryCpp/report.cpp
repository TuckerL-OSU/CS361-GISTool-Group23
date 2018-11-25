#include<iostream>
#include<cmath>
#include<string>
#include <vector>
#include<limits>
#include<iomanip>
#include<stdlib.h>
#include "report.hpp"

using namespace std;

Report::Report(){
  int paramNum = 0;
  int curFill = 0;
  std::vector <std::string> paramNames;
}

void Report::setParaNumber(int number){
  paramNum = number;
  cout << "Number of parameters: " << paramNum << endl;
}

void Report::setParaNames(const char *param){
      paramNames.push_back( param);
}


std::string Report::getParaName(int pos) {
      return paramNames[pos];
}

int Report::getParaNumber(){
      return paramNum;
}
