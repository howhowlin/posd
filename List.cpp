#include "list.h"
#include <string>
#include <iostream>
#include <typeinfo>
#include "variable.h"
using std::string;

string List::get() const{
  return "List";
}

Term * List::elements(int index) { //??
  return _elements[index];
}

Term * List::head() const{
    if(this->value()=="[]"){
      throw "Accessing head in an empty list";
    }
    return _elements[0];
  // catch(const char* message){
    //  std::cout << message << '\n';
  //  }
}

List * List::tail() const{
  if(this->value()=="[]"){
    throw "Accessing head in an empty list";
  }
   
  vector<Term *> args;
  args.assign(_elements.begin()+1,_elements.end());
   List* list = new List(args);
  return list;

}


string List::symbol() const{
  string ret="";
  if(_elements.size()>0){
     ret="[";
    for(int i=0;i<_elements.size()-1;i++){
      ret += _elements[i]-> value()+", ";
    }
    ret +=_elements[_elements.size()-1]-> value()+"]";
     return ret;
   }
  else
      ret= "[]";
    return ret;
}


string List::value() const{
  string ret="";
  if(_elements.size()>0){
     ret="[";
    for(int i=0;i<_elements.size()-1;i++){
      ret += _elements[i]-> value()+", ";
    }
    ret +=_elements[_elements.size()-1]-> value()+"]";
     return ret;
   }
  else
      ret= "[]";
    return ret;
}

bool List::match(Term &term){

  _inst =&term;
//  std::cout << _inst->get() << '\n';


 if (_inst->get()=="Variable"){
     return true;
  }
  else if(_inst->get()=="Atom"){
    return false;
  }

  else if(_inst->get()=="List"){
   List &list = static_cast<List&>(term);
     for(int i=0;i<_elements.size();i++){
       if(_elements[i]->symbol()!=list.elements(i)->symbol()){
         if(_elements[i]->get()=="Variable"){
           _elements[i]->match(*list.elements(i));
              return true;
            }
          else
              return false;
         }
      }
      return true;
   }
   else{
      return false;
   }
 }

List::List(): _elements(){
}
List::List (vector<Term *> const & elements):_elements(elements){

}
