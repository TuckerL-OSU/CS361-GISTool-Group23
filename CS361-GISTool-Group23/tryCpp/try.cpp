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

int main(int argc, char const *argv[]) {
  Report newReport;
  std::cout << argc-1 << '\n';

  newReport.setParaNumber(argc-1);

  for(int i = 1; i < argc; ++i){
          //cout << argv[i] << '\n';
          newReport.setParaNames(argv[i]);
  }

  ofstream outfile ("test.txt");
  outfile << "Number of Parameters: " << newReport.getParaNumber() << endl;
  for (int i = 0; i < newReport.getParaNumber(); i++) {
      outfile << "File "<< i << ": " << newReport.getParaName(i) << std::endl;
  }
  outfile.close();


}
