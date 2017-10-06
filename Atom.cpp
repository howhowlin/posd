#include "number.h"
#include "atom.h"
#include "variable.h"
#include <string>

using std::string;
bool Atom::match(Number a){
  _assignable=false;
   return _assignable;
}

bool Atom::match(Variable& a){
  if(a._come){
    _assignable=true;
    a._symbol=_symbol;
    a._come=false;
  }
  else{
    if(_symbol==a._symbol){
      _assignable=true;
    }
    else{
      _assignable=false;
    }

  }
  return _assignable;
}
