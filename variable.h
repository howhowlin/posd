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
  int signal2(int a);
  void setPoint(Variable * ps);
  void setValue(string s1);

  bool match(Term & term);

private:
  bool _signal = false;
  bool _signal2 = false;
  string _value;
  Variable *v1;
  Variable *_this;
  bool _assignable = true;
};

#endif
