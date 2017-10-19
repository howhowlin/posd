#ifndef ATOM_H
#define ATOM_H
#include "term.h"
#include <string>
using std::string;

class Atom : public Term{
public:
  string _symbol;
  bool match(Term &term);
  Atom (string s);       // 1. 建構
  string symbol() const; // 2. 回傳Ｓymbol
private:
bool _assignable = true;

};


#endif
