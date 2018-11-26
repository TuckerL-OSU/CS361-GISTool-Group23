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


int main(int argc, char const *argv[]){
//Create Report
/******************************************************************************/
  //cout << argc << endl;
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

  //create and open file for report
  ofstream outfile ("Report.txt");
  outfile << "Number of Images: " << newReport.getNumberOfArgs() << endl;

  //print into report the file names
  for (int i = 0; i < newReport.getNumberOfArgs(); i++) {
      outfile << "File "<< i+1 << ": " << newReport.getParaName(i) << std::endl;
  }
  //print into report type of damage Analysis
  outfile << "Type of Damage Analysis: " << newReport.getDamageType() << endl;
/******************************************************************************/


/*

Create a report by function
newReport.setReport( parameter 1, parameter 2);
  parameter 1:
  parameter 2: int input, 1 if true, 2 if false.

newReport.setReport("typea" , 0);
newReport.setReport("typeb" , 1);
newReport.setReport("typec" , 0);
newReport.setReport("typed" , 1);
newReport.setReport("typee" , 1);
newReport.setReport("typef" , 1);
newReport.setReport("typey" , 0);
*/



//attach to the end of the main function

for (int i = 0; i < newReport.getNumberReports(); i++) {
  outfile << newReport.printReports(i) << endl;
}

//Close file
outfile.close();
}
