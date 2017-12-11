#ifndef LIST_H
#define LIST_H

#include "term.h"
#include "atom.h"
#include <vector>
using std::vector;

class List : public Term {
public:
  string symbol() const;
  string value() const;
  bool match(Term & term);
  string getName() const;
  Atom * name() const;
  Iterator<Term*> * createIterator();
  Iterator<Term*> * createDFSIterator();
  Iterator<Term*> * createBFSIterator();
public:
  List (): _elements() {}
  List (vector<Term *> const & elements);
  Term * elements(int index) const;
  Term * head() const;
  List * tail() const;
  void set(vector<Term *> const & elements);
  int arity() const {return _elements.size();}
private:
  vector<Term *> _elements;


};

#endif
