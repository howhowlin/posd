#include "atom.h"
#include "variable.h"
#include "number.h"

Variable::Variable(string s){
 _symbol=s;
 _value =s;
}

string Variable::value() const{
  return  _value;
}
string Variable::symbol() const{
  return _symbol;
}


bool Variable::match(Term & term){
  Atom * ps = dynamic_cast<Atom *>(&term);
  bool ret = _assignable;
  if(_assignable){
    _value = ps->symbol() ;
    _assignable = false;
  }
  return ret;
}
