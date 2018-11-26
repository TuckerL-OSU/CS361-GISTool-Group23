#ifndef  REPORT_HPP
#define REPORT_HPP
using namespace std;

class Report{
public:
  int paramNum;
  string damage_type;
  string typeOfAnalysis;
  int numberOfArgs;
  vector<string> paramNames;
  int curFill;
  Report();
  void setType(const char *param);
  void setParaNumber(int number);
  void setParaNames(const char * array);
  std::string getParaName(int pos);
  int getParaNumber();
  int getNumberOfArgs();
  string getDamageType();
};

#endif
