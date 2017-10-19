#include "variable.h"
#include "atom.h"
#include "number.h"


Variable::Variable(string s){
  _symbol = s;
  _value = s;
}
string Variable::symbol() const{
  return _symbol;
}
string Variable::value() const {
  return _value;
}
void Variable::setValue(string s1) {
  _value = s1;
}


bool Variable::match(Term & term){
 singal = _assignable;
       Atom * aps = dynamic_cast<Atom *>(&term);
          if(aps){
            if(singal){
              _value = aps->value();
              if(flag){
               p1->setValue(aps->value());
              }
              _assignable = false;
          }
         }

       Number * nps = dynamic_cast<Number *>(&term);
             if(nps){
               if(singal){
                  setValue(nps->value());
                  if(flag1){
                      if(it->value()=="1")
                         p1->setValue(nps->value());
                      else
                         it->setValue(nps->value());
                   }
                }
                 _assignable = false;
            }

     return singal;
}
