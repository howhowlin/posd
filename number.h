#ifndef NUMBER_H
#define NUMBER_H

#include <sstream>
#include <string>
#include "term.h"
using namespace std;

class Number : public Term{
public:
  string get() const;
  Number(double db);
};
#endif
