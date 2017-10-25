#ifndef ATOM_H
#define ATOM_H
#include "term.h"
#include <string>
#include <sstream>
using std::string;


class Atom : public Term{
public:
  string  get() const;
  Atom(string s):Term(s) {}
};

#endif
