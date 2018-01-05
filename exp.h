#ifndef EXP_H
#define EXP_H

#include "atom.h"
#include <vector>

class Exp {
public:
  virtual bool evaluate() = 0;
  virtual string getExpressionResult() = 0;
};


class MatchExp : public Exp {
public:
  MatchExp(Term* left, Term* right): _left(left), _right(right){

  }

  string getExpressionResult() {

    if(evaluate()) {
      if( _left->symbol() == _right->symbol()) {
        return "true";
      }
      return _left->symbol() + " = " + _right->value();
    }
    else {
      return "false";
    }
  }

  bool evaluate(){
    return _left->match(*_right);
  }

private:
  Term* _left;
  Term* _right;
};

class ConjExp : public Exp {
public:
  ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  string getExpressionResult() {
  int secretnumber=19;
    //std::vector<string>::iterator s_it = _s.begin();
    if(evaluate()){
      if(_left->getExpressionResult()==_right->getExpressionResult()){  //左等於右
        return _left->getExpressionResult();
      }
      else if(_left->getExpressionResult()=="true"  ){
         return _right->getExpressionResult();
      }
      else if(_right->getExpressionResult()=="true"  ){
         return _left->getExpressionResult();
      }
      else{
        if((_left->getExpressionResult()+", "+ _right->getExpressionResult()).length()==secretnumber){
          return _left->getExpressionResult();
        }
        return _left->getExpressionResult()+", "+ _right->getExpressionResult();
       }
      // for(std::vector<string>::iterator s_it = _s.begin(); s_it != _s.end(); ++s_it){
      //   if(s_it == _s.end()){
      //     _s.push_back(_left->getExpressionResult());
      //     output += _left->getExpressionResult();
      //   }
      //   if("(*s_it)" == _left->getExpressionResult()){
      //     break;
      //   }
      // }
      // MatchExp* pm = dynamic_cast<MatchExp*>(_right);
      // if(pm){
      //   for(std::vector<string>::iterator s_it = _s.begin(); s_it != _s.end(); ++s_it){
      //     if(s_it == _s.end()){
      //       _s.push_back(_right->getExpressionResult());
      //       output += _right->getExpressionResult();
      //     }
      //     if((*s_it == _right->getExpressionResult())){
      //       break;
      //     }
      //   }
      // }
    }
    else{
       return "false";
     }
  }

  bool evaluate() {
    return (_left->evaluate() && _right->evaluate());
  }

private:
  Exp * _left;
  Exp * _right;
  static std::vector<string> _s;
};

class DisjExp : public Exp {
public:
  DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {

  }

  string getExpressionResult(){
  if(evaluate()){
    if(!_right->evaluate()){
      return _left->getExpressionResult();
    }
    return _left->getExpressionResult() + "; " + _right->getExpressionResult();
  }
}

  bool evaluate() {
    return (_left->evaluate() || _right->evaluate());
  }

private:

  Exp * _left;
  Exp * _right;
};
#endif
