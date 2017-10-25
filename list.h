#ifndef LIST_H
#define LIST_H

#include "term.h"
#include <string>
using std::string;
#include <vector>
using std::vector;

class List : public Term {
public:
  string symbol() const;
  string value()  const;
  string get()    const;
  bool match(Term &term);

public:
  List ();
  List (vector<Term *> const & elements);
  Term * elements(int index);
  // Term * head() const;
  // List * tail() const;

private:
  vector<Term *> _elements;
};

#endif
