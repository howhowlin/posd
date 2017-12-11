#ifndef NODE_H
#define NODE_H
#include <typeinfo>
#include "atom.h"
enum Operators {SEMICOLON, COMMA, EQUALITY, TERM};

class Node {
public:
  Node(Operators op):payload(op), term(0), left(0), right(0) {}
  Node(Operators op, Term *t, Node *l, Node *r):payload(op), term(t), left(l), right(r) {}
  bool evaluate(){
   if(this->payload==EQUALITY){
       if(this->left->term->get()=="Number" && this->right->term->get()=="Number"){
          return false;
        }
        else  {
          this->left->term->match(*this->right->term);
          return true;
        }
   }

    else  if(this->payload==COMMA&&this->left->payload==EQUALITY&&this->right->payload==EQUALITY){
        if(this->left->left->term->get()=="Variable" && this->left->right->term->get()=="Number" &&this->right->left->term->get()=="Variable" && this->right->right->term->get()=="Number"){
          if(this->left->left->term->symbol()!=this->right->left->term->symbol()){
           this->left->left->term->match(*this->left->right->term);
           this->right->left->term->match(*this->right->right->term);
            return true;
           }
           else {
             return false;
           }

        }
        else if(this->left->left->term->get()=="Variable" && this->left->right->term->get()=="Number" &&this->right->left->term->get()=="Variable" && this->right->right->term->get()=="Variable"){
           this->left->left->term->match(*this->left->right->term);
           this->right->left->term->match(*this->left->right->term);
           return true;
        }
        else if(this->left->left->term->get()=="Variable" && this->left->right->term->get()=="Variable" &&this->right->left->term->get()=="Variable" && this->right->right->term->get()=="Number") {
           this->left->left->term->match(*this->right->right->term);
           this->left->right->term->match(*this->right->right->term);
           return true;
        }

        else if(this->left->left->term->get()=="Variable" && this->left->right->term->get()=="Struct" &&this->right->left->term->get()=="Variable" && this->right->right->term->get()=="Number") {
           this->right->left->term->match(*this->right->right->term);
           this->left->left->term->match(*this->left->right->term);
           return true;
        }

        else{
          return false;
        }

      }

   else  if(this->payload==COMMA&&this->left->payload==EQUALITY&&this->right->payload==COMMA){
      this->left->left->term->match(*this->left->right->term);
      this->right->left->left->term->match(*this->right->left->right->term);
      this->right->right->left->term->match(*this->right->right->right->term);

      return true;
    }
   else if(this->payload==SEMICOLON){
       this->left->left->term->match(*this->left->right->term);
       this->right->left->term->match(*this->right->right->term);

      return true;
   }

    else{
      return false;
    }
  }

    Operators payload;
    Term * term;
    Node * left;
    Node * right;
};

#endif
