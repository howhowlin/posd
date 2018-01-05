#ifndef TERM_H
#define TERM_H

#include <string>
#include <sstream>
using std::string;

template <class T>
class Iterator;
class Struct;
class Variable;
class List;
class Term{
  friend class Parser;
public:
  virtual string symbol() const {return _symbol;}
  virtual string value() const {return symbol();}
  virtual bool match(Term & a);
  virtual Iterator<Term*> * createIterator();
  virtual string getName() const{return "Term";}

  virtual Struct* getStruct(){
    return nullptr;
  }

  virtual Variable* getVariable(){
    return nullptr;
  }

  virtual List* getList(){
    return nullptr;
  }
  Term ():_symbol(""){}
protected:
  //Term ():_symbol(""){}
  Term (string s):_symbol(s) {}


  string _symbol;
};

#endif
