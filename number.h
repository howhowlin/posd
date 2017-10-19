#ifndef NUMBER_H
#define NUMBER_H

#include <sstream>
#include <string>
#include "term.h"
using namespace std;

class Number : public Term{
  public:
    Number(double s);
    string symbol() const;
    string value() const;
   bool match(Term &term);
  private:
    string s_value;
    double _value;
    bool _assignable = true;
};
#endif
