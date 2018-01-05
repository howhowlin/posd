#include "variable.h"
#include <iostream>

using namespace std;
string Variable::getName() const {
  return "Variable";
}
string Variable::value() const {
  if (_instance)
    return _instance->value();
  else
    return Term::value();
}
bool Variable::match( Term & term ){
  if (_instance != nullptr)
    return _instance->match(term);
  if(&term != this)
    _instance = &term ;
  return true;

}
