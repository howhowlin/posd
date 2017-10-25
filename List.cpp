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


}
List * List::tail() const{

  
}


string List::symbol() const{
  string ret="";
  if(_elements.size()>0){
     ret="[";
    for(int i=0;i<_elements.size()-1;i++){
      ret += _elements[i]-> value()+",";
    }
    ret += " "+_elements[_elements.size()-1]-> value()+"]";
     return ret;
   }
  else
      ret= "[]";
    return ret;
}


string List::value() const{
   return "";
}

bool List::match(Term &term){

  if(typeid(term)==typeid(Variable))
      return true;

  else if(typeid(term)==typeid(List)){
   List &list = static_cast<List&>(term);  //??
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
   }
   return true;

 }


List::List(): _elements(){

}
List::List (vector<Term *> const & elements):_elements(elements){


}
