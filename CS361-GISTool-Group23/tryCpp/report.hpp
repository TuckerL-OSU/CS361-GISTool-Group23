#ifndef  REPORT_HPP
#define REPORT_HPP
using namespace std;

class Report{
public:
  int paramNum;
  int numberOfReports;
  string damage_type;
  string typeOfAnalysis;
  int numberOfArgs;
  vector<string> paramNames;
  vector <string> functionNames;
  std::vector <int> functionStatus;
  int curFill;
  Report();
  void setType(const char *param);
  void setParaNumber(int number);
  void setParaNames(const char * array);
  std::string getParaName(int pos);
  int getParaNumber();
  int getNumberOfArgs();
  string getDamageType();
  void setReport(string reportName, int successNumber);
  int getNumberReports();
  string printReports(int section);
};
#endif
