#include "number.h"

string Number::get() const{
    return "Number";
}

Number::Number(double db):Term(db) {

}

bool Number::match(Term &term){
   return false;
}
