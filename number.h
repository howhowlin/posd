#ifndef NUMBER_H
#define NUMBER_H

#include <string>

using std::string;

class Variable;
class Atom;

class Number{
public:
  Number(int s):i_value(s){}
  int  i_value;

  Number(string s):s_symbol(s){}
  string  s_symbol;


  string value();   //method  .value()
  string symbol();
  bool match(Number a);
  bool match(Atom a);
  bool match(Variable a);


private:
     string s_value;
     bool _assignable;
 };

#endif
