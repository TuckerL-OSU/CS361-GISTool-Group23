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
  string damage_type;
  int numberOfArgs = 0;
  string typeOfAnalysis;
  int paramNum = 0;
  int curFill = 0;
  int numberOfReports = 0;
  std::vector <std::string> paramNames;
  std::vector <std::string> functionNames;
  std::vector <int> functionStatus;
}

void Report::setParaNumber(int number){
  paramNum = number;
  cout << "Number of parameters: " << paramNum << endl;
}

void Report::setType(const char *param){
    typeOfAnalysis = param;
    if(typeOfAnalysis.compare("./imagecompar")!=0){
      numberOfArgs = paramNum;
      damage_type = "none";
      cout << "./imagecompar: " << numberOfArgs << endl;
    }else if(typeOfAnalysis.compare("./testsuite")==0){
      numberOfArgs = paramNum-1;
      damage_type = paramNames[paramNum-2];
      cout << "number of args: " << numberOfArgs << "type of damage" << damage_type << endl;
    }
}

void Report::setParaNames(const char *param){
      paramNames.push_back(param);
}


std::string Report::getParaName(int pos) {
      return paramNames[pos];
}

int Report::getParaNumber(){
      return paramNum;
}

int Report::getNumberOfArgs(){
      return numberOfArgs;
}

string Report::getDamageType(){
      return damage_type;
}

void Report::setReport(string reportName, int successNumber){
    functionNames.push_back(reportName);
    functionStatus.push_back(successNumber);
    numberOfReports++;
}

int Report::getNumberReports(){
    return numberOfReports;
}


string Report::PrintReports(int section){
    string item = functionNames[section] + functionStatus[section];
    return item;
}
