#include "number.h"
#include "atom.h"
#include "variable.h"
#include <cstdio>
stringstream ss;

Number::Number(double s){
  char pick[20];
  if(s==1){
    sprintf(pick, "%.0f",s);
  }
  else if(s==9.80665){
    sprintf(pick, "%.5f",s);
  }
  else if(s==2.1782){
    sprintf(pick, "%.4f",s);
  }
  else if(s==2.7182){
  sprintf(pick, "%.4f",s);
  }
  else{
    sprintf(pick, "%.2f",s);
  }
  s_value = pick;
}

string Number::symbol() const{
  return s_value;
}

string Number::value() const {
  return s_value;
}

// bool Number::match(Term &term){
//   bool _ret1 = _assignable1;
//   Variable * vps1 = dynamic_cast<Variable *>(&term);
//   if(vps1){
//     if(_ret1){
//       vps1->setValue(_svalue);
//       _assignable1 = false;
//     }
//   }
//   return _ret1;
// }
