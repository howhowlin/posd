#include "variable.h"
#include "atom.h"
#include "list.h"
#include <iostream>

string Variable::value() const {
  if (_inst)
    return _inst->symbol();
  else
    return Term::symbol();
}

string Variable::get() const {
    return "Variable";
}


bool Variable::match( Term & term ){
  if (this == &term)
    return true;
  if(!_inst){
    _inst = &term ;
    if(_inst->get()=="Atom"){
      //std::cout << " "+_inst->symbol() << '\n';
    }
    return true;
  }
  return _inst->match(term);
}
