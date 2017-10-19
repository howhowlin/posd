#ifndef VARIABLE_H
#define VARIABLE_H
#include <iostream>
#include <string>
#include "term.h"
using std::string;
using namespace std;
class Term;
class Variable :public Term{
public:
  Variable(string s);
  string _symbol;
  string symbol() const;
  string value() const;
  void setValue(string s1);
  bool match(Term & term);

private:
  bool flag = false;
  bool flag1 = false;
  Variable *p1;
  Variable *it;
  string _value;
  bool _assignable = true;
  bool singal ;

};

#endif
