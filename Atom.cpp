#include "atom.h"
#include "variable.h"

Atom::Atom(string s ){
  _symbol = s;
}
string Atom::symbol()const{
  return _symbol;
}

bool Atom::match(Term & term){
  Variable * p1 = dynamic_cast<Variable *>(&term);
  bool singal =_assignable;
  if(p1){
    if(singal){
       p1->setValue(_symbol);
      _assignable=false;
    }
  }
  Atom * p2 = dynamic_cast<Atom *>(&term);
  if(p2){
    return symbol() == p2->symbol();
  }
 return singal;

}
