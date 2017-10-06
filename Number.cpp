#include "atom.h"
#include "variable.h"
#include "number.h"


string Number::value(){
 s_value = std::to_string(i_value);
 return s_value;
 }

 string Number::symbol(){
   return s_symbol;
 }

bool Number::match(Number a){
  if(i_value==a.i_value)
    _assignable=true;
  else
    _assignable=false;

  return _assignable;
}

bool Number::match(Atom a){
   _assignable=false;
   return _assignable;
 }


 bool Number::match(Variable a){
    if(a._come){
      _assignable=true;
    }
    else{
      _assignable=false;
    }
  return _assignable;

}
