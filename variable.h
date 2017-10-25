#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
using std::string;

class Variable : public Term {
public:
  Variable(string s):Term(s), _inst(0){}
  string value() const ;      //value()
  bool match( Term & term );  //match()
  string get() const ;
  //Term * elements(int index);

private:
  Term * _inst;
};

#endif
