#ifndef VARIABLE_H
#define VARIABLE_H
using namespace std;


#include "term.h"
#include <string>
#include <iostream>
using std::string;

class Term;
class Variable:public Term{
public:
  Variable(string s);
  string  _symbol;
  string value() const;
  string symbol() const;
  void setValue(string s1);
  bool match(Term & term) ;

private:
  string _value;
  bool _assignable = true;
};

#endif
