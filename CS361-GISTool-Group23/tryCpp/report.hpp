#ifndef  REPORT_HPP
#define REPORT_HPP
using namespace std;

class Report{
public:
  int paramNum;
  vector<string> paramNames;
  int curFill;
  Report();
  void setParaNumber(int number);
  void setParaNames(const char * array);
  std::string getParaName(int pos);
  int getParaNumber();
};

#endif
