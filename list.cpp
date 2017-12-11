
#include "variable.h"
#include "iterator.h"
#include <typeinfo>
#include "list.h"
#include "number.h"
#include <iostream>

using namespace std;
string List::getName() const{
  return "List";
}

List::List(vector<Term *> const & elements){
  _elements = elements;
}
Term * List::elements(int index) const{
  return _elements[index];
}
Atom * List::name() const{
  Atom *a = new Atom("[]");
  return a;
}


string List::symbol() const{
  string _ret = "[";
  std::vector<Term *>::const_iterator it = _elements.begin();
  if(_elements.empty()){
    return "[]";
  }
  for(;it != _elements.end()-1;++it)
    _ret += (*it)->symbol()+", ";
  _ret += (*it)->symbol()+"]";

  return _ret;
}
string List::value() const{
  string _ret = "[";
  std::vector<Term *>::const_iterator it = _elements.begin();
  if(_elements.empty()){
    return "[]";
  }
  else{
  for(;it != _elements.end()-1;++it)
    _ret += (*it)->value()+", ";
  _ret += (*it)->value()+"]";

  return _ret;
  }
}
bool List::match(Term& term){
  bool _ret = true;
  if(typeid(term)==typeid(Variable)){
      return _ret;
  }
  else if(typeid(term)==typeid(List)){
      List &list = static_cast<List&>(term);
      for(int i=0;i<_elements.size();i++){
        if(_elements[i]->symbol()!=list.elements(i)->symbol()){
            if(_elements[i]->get()=="Variable"){
              _elements[i]->match(*list.elements(i));
            }
        }
      }
      return _ret;
  }
  else{
      return symbol() == term.symbol();
  }
}

Term * List::head() const{
  if(this->value()=="[]"){
    throw string("Accessing head in an empty list");
  }
  else{
  return _elements[0];
   }
}
List * List::tail() const{
   if(this->value()=="[]"){
    throw string("Accessing tail in an empty list");
   }
   else{
  std::vector<Term*>  _elements1;
  _elements1.assign(this->_elements.begin()+1,this->_elements.end());
  List* list = new List(_elements1);
  return list;
   }
 }
void List::set(vector<Term *> const & elements){
  _elements = elements;
}

Iterator<Term*> * List::createIterator(){
  return new ListIterator(this);
}

Iterator<Term*> * List::createDFSIterator(){
    return new DFSIterator(this);
}

Iterator<Term*> * List::createBFSIterator(){
    return new BFSIterator(this);
}
