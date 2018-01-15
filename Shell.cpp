#include <gtest/gtest.h>


#include "exception.h"
#include "expression.h"

#include <string.h>
#include "atom.h"
#include "variable.h"
#include "exp.h"
#include "parser.h"

using namespace std;


int main( int argc , char **argv )
{
  string input;
  string finalInput;
  string result;
  cout << "?- ";
    while(getline (cin,input)){
        if(input=="halt."){
          break;
        }
        else if(input.length()==0){
          cout << "?- ";
        }
        else if(input.find(";")!=-1&&input.find(".")==-1){
          finalInput=finalInput+input;
          cout << "|   " ;
        }
        else{
          finalInput=finalInput+" "+input;
          Scanner s(finalInput);
          Parser p(s);
          try{
          p.buildExpression();
           result = p.getExpressionResult();
        }
        catch (std::string &msg) {
           result = msg;// it should throw an exception like this.
        }
          std::cout << result << '\n';
          finalInput="";
          result="";
          cout << "?- ";
        }
    }
}
