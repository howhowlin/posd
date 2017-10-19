#include "atom.h"
#include "variable.h"

Atom::Atom(string s ){
  _symbol = s;
}
string Atom::symbol()const{
  return _symbol;
}
