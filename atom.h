#ifndef ATOM_H
#define ATOM_H

#include <string>
#include <stdio.h>

using std::string;

class Number;
class Variable;
class Atom {
public:
  Atom (string s):_symbol(s){
    _assignable=false;
  }
  string _symbol;

  bool match(Number a);
  bool match(Variable& a);

private:
  bool _assignable;

};

#endif
