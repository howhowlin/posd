#ifndef PARSER_H
#define PARSER_H
#include <string>
using std::string;

#include "scanner.h"
#include "term.h"
#include "number.h"
#include "variable.h"
#include "atom.h"
#include "struct.h"
#include "list.h"

class Parser{
public:
  Parser(Scanner scanner) : _scanner(scanner){}
  Term* createTerm(){
    int token = _scanner.nextToken();
    if(token == VAR)
        return new Variable(symtable[_scanner.tokenValue()].first);
    else if(token == NUMBER)
        return new Number(_scanner.tokenValue());
    else if(token == ATOM){
        Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
        if(_scanner.currentChar() == '(' ) {
          _scanner.nextToken() ;
          vector<Term*> terms = getArgs();
          if(terms.size()==0){
              return new Struct(*atom,terms);
            }
          if(_currentToken == ')')
            return new Struct(*atom, terms);
        }
        else
          return atom;
       }
    else if(token == 91) {   //大括號
        vector<Term *> _elements = getArgs();
      if(_scanner.nChar(_scanner.bValue()) == ')'){  // 碰到）
          throw string("unexpected token");
        }
      else
        _scanner.nspace();                        //一般處理
       return new List(_elements);
      if(_scanner.nextToken() == 93)
           return new List();
    }

    else if(token == ATOMSC){       //ATOMSC
       if(_scanner.currentChar() == '('){
         Atom* atom = new Atom(symtable[_scanner.tokenValue()].first);
         _scanner.nextToken();
         vector<Term *> terms = getArgs();
       if(_currentToken == ')')
          return new Struct(*atom,terms);
        }
      }

    else {
         Term *term = new Term();
         return term;
       }
  }

  vector<Term*> getArgs()
  {
    Term* term = createTerm();
    vector<Term*> args;
    if(term->symbol() == "")   // 不要push_back
        return args;

      args.push_back(term);
    while((_currentToken = _scanner.nextToken()) == ',') {
      args.push_back(createTerm());
    }
    return args;
  }

private:
  Scanner _scanner;
  int _currentToken;
};
#endif
