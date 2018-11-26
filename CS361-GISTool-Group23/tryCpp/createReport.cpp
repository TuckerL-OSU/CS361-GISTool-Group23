#include <iostream>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <fstream>
#include "report.hpp"

using namespace std;


void createReport(int argc, char const *argv[]){
  /****** Create Report *******/
  Report newReport;
  //set Parameter numbers
  newReport.setParaNumber(argc-1);
  //Store number of
  for(int i = 1; i < argc; ++i){
          newReport.setParaNames(argv[i]);
  }
  //store type of function that ran it
  newReport.setType(argv[0]);
  ofstream outfile ("Report.txt");
  outfile << "Number of Images: " << newReport.getNumberOfArgs() << endl;

  for (int i = 0; i < newReport.getNumberOfArgs(); i++) {
      outfile << "File "<< i+1 << ": " << newReport.getParaName(i) << std::endl;
  }

  outfile << "Type of Damage Analysis: " << newReport.getDamageType();
  outfile.close();
}


int main(int argc, char const *argv[]) {
  //cout << argc << endl;
  createReport(argc, argv);
}
