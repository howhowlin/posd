#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;
#include "atom.h"
#include "variable.h"
#include "global.h"
#include "scanner.h"
#include "struct.h"
#include "list.h"
#include "number.h"
#include "node.h"
#include "utParser.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner), _terms(){}

  Term* createTerm(){
    int token = _scanner.nextToken();
    _currentToken = token;
    if(token == VAR){
      return new Variable(symtable[_scanner.tokenValue()].first);
    }
    else if(token == NUMBER){
      return new Number(_scanner.tokenValue());
    }
    else if(token == ATOM || token == ATOMSC){
      Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
      if(_scanner.currentChar() == '(' ) {
        return structure();
      }
    else
        return atom;
    }
    else if(token == '['){
      return list();
    }
    return nullptr;
  }

  Operators createOperator(){
     if(_currentToken=='='){
       return EQUALITY;
     }
     else if (_currentToken==','){
       return COMMA;
     }
     else if (_currentToken==';'){
       return SEMICOLON;
     }
  }




  void matchings(){
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);

      while((_currentToken = _scanner.nextToken()) == '=' ||_currentToken  == ',' ||_currentToken  == ';') {
        _operators.push_back(createOperator());
        _terms.push_back(createTerm());
      }
    }
  }

  Node * expressionTree(){
   if(_terms.size()==2){
    Node * leftchild = new  Node(TERM,_terms[0],nullptr,nullptr);
    Node * rightchild= new  Node(TERM,_terms[1],nullptr,nullptr);
    Node * root = new Node(EQUALITY,nullptr,leftchild,rightchild);
    return root;
  }
   if(_terms.size()==4){
      if(_operators[1]==1){
        Node * llchild  = new  Node(TERM,_terms[0],nullptr,nullptr);
        Node * lrchild  = new  Node(TERM,_terms[1],nullptr,nullptr);
        Node * rlchild = new  Node(TERM,_terms[2],nullptr,nullptr);
        Node * rrchild = new  Node(TERM,_terms[3],nullptr,nullptr);
        Node * leftchild = new  Node(EQUALITY,nullptr,llchild,lrchild);
        Node * rightchild= new  Node(EQUALITY,nullptr,rlchild,rrchild);
        Node * root      =   new Node(COMMA,nullptr,leftchild,rightchild);
        return root;
      }
      else if(_operators[1]==0){
        Node * llchild  = new  Node(TERM,_terms[0],nullptr,nullptr);
        Node * lrchild  = new  Node(TERM,_terms[1],nullptr,nullptr);
        Node * rlchild = new  Node(TERM,_terms[2],nullptr,nullptr);
        Node * rrchild = new  Node(TERM,_terms[3],nullptr,nullptr);
        Node * leftchild = new  Node(EQUALITY,nullptr,llchild,lrchild);
        Node * rightchild= new  Node(EQUALITY,nullptr,rlchild,rrchild);
        Node * root     =   new Node(SEMICOLON,nullptr,leftchild,rightchild);
        return root;
      }

   }
   if(_terms.size()==6){
     Node * llchild  = new  Node(TERM,_terms[0],nullptr,nullptr); //x
     Node * lrchild  = new  Node(TERM,_terms[1],nullptr,nullptr); //1
     Node * rllchild = new  Node(TERM,_terms[2],nullptr,nullptr);   //Y
     Node * rlrchild = new  Node(TERM,_terms[3],nullptr,nullptr);    //2
     Node * rrlchild = new  Node(TERM,_terms[4],nullptr,nullptr);    //Z
     Node * rrrchild = new  Node(TERM,_terms[5],nullptr,nullptr);    //3
     Node * rlchild = new   Node(EQUALITY,nullptr,rllchild,rlrchild);//=
     Node * rrchild = new   Node(EQUALITY,nullptr,rrlchild,rrrchild);//=


     Node * leftchild = new  Node(EQUALITY,nullptr,llchild,lrchild);
     Node * rightchild= new  Node(COMMA,nullptr,rlchild,rrchild);
     Node * root    =   new Node(COMMA,nullptr,leftchild,rightchild);
     return root;
   }
  }

  Term * structure() {
    Atom structName = Atom(symtable[_scanner.tokenValue()].first);
    int startIndexOfStructArgs = _terms.size();
    _scanner.nextToken();
    createTerms();
    if(_currentToken == ')')
    {
      vector<Term *> args(_terms.begin() + startIndexOfStructArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfStructArgs, _terms.end());
      return new Struct(structName, args);
    } else {
      throw string("unexpected token");
    }
  }

  Term * list() {
    int startIndexOfListArgs = _terms.size();
    createTerms();
    if(_currentToken == ']')
    {
      vector<Term *> args(_terms.begin() + startIndexOfListArgs, _terms.end());
      _terms.erase(_terms.begin() + startIndexOfListArgs, _terms.end());
      return new List(args);
    } else {
      throw string("unexpected token");
    }
  }

  vector<Term *> & getTerms() {
    return _terms;
  }

private:
  FRIEND_TEST(ParserTest, createArgs);
  FRIEND_TEST(ParserTest,ListOfTermsEmpty);
  FRIEND_TEST(ParserTest,listofTermsTwoNumber);
  FRIEND_TEST(ParserTest, createTerm_nestedStruct3);

  void createTerms() {
    Term* term = createTerm();
    if(term!=nullptr)
    {
      _terms.push_back(term);
      while((_currentToken = _scanner.nextToken()) == ',') {
        _terms.push_back(createTerm());
      }
    }
  }
  vector<Operators > _operators;
  vector<Term *> _terms;
  Scanner _scanner;
  int _currentToken;
};
#endif
