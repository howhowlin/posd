#include "atom.h"
#include "variable.h"
#include "number.h"

bool Variable::value(){
  return _value;
}

bool Variable::match(Number a){
   if(_assign){
   _assignable=true;
   _assign=false;
   }
   else{
     _assignable=false;
   }
   return _assignable;
}


bool Variable::match(Atom a){
  if(_come){
   _symbol = a._symbol;
   _come=false;
   _assignable=true;
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
