#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "term.h"
using std::string;

class Variable : public Term {
public:
  Variable(string s):Term(s), _instance(0){}
  string value() const;
  bool match( Term & term );

  string getName() const;

  Variable* getVariable(){
    return this;
  }
private:
  Term * _instance;
};

#endif
