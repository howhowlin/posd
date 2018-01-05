#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
#include <string>
#include <sstream>
using std::string;


class Number : public Term{
public:
  Number(double db){
    std::ostringstream strs;
    strs <<db;
    _symbol = strs.str();
  }
  string getName();
};

#endif
