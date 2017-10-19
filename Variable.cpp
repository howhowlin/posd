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
int Variable::signal2(int a){
  _signal2 = a;
}
void Variable::setPoint(Variable * ps){
  _this = ps;
}
bool Variable::match(Term & term){
  bool _ret = _assignable;
  Atom * aps = dynamic_cast<Atom *>(&term);
  if(aps){
    if(_ret){
      _value = aps->value();
      if(_signal){
       v1->setValue(aps->value());
      }
      _assignable = false;
  }

 }

 Number * nps = dynamic_cast<Number *>(&term);

 if(nps){
   //cout << nps << endl;
   //cout << nps->value() << endl;
   if(_ret){
      setValue(nps->value());
      cout << "test2" << endl;
      cout << _signal2 << endl;
      if(_signal2){
        cout << "test123" << endl;
        if(_this->value()=="1"){
        v1->setValue(nps->value());
        cout << v1->value() << endl;
        }
        else{
          _this->setValue(nps->value());
        }

     }
  }
     _assignable = false;
}

  Variable * vps = dynamic_cast<Variable *>(&term);
  if(vps){
    if(!_signal){
      v1 = vps;
      _this = this;
      vps->signal2(1);
      vps->setPoint(this);
      _value = vps->value();
      _signal2 = true;
      cout << _signal2 << endl;
      cout << "test1" << endl;
    }
    _signal = true;
  }
  return _ret;
}
