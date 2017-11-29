#ifndef UTPARSER_H
#define UTPARSER_H

#include <string>

#include "parser.h"
#include "scanner.h"

class ParserTest : public ::testing::Test {
protected:
  void SetUp() {
    symtable.clear();
  }
};

TEST_F(ParserTest, OneMatching) {
  Scanner scanner("X=1.");
  Parser parser(scanner);
  parser.matchings();
  vector<Term *> terms = parser.getTerms();
  EXPECT_EQ(2, terms.size());
  EXPECT_EQ("X", terms[0]->symbol());
  EXPECT_EQ("1", terms[1]->symbol());
  EXPECT_NE("1", terms[0]->value());
  Node * et = parser.expressionTree();
  EXPECT_EQ(EQUALITY, et->payload);
  EXPECT_TRUE(et->evaluate());
  EXPECT_EQ("1", terms[0]->value());
}

TEST_F(ParserTest, OneMatchingFalse) {
  Scanner scanner("1=2.");
  Parser parser(scanner);
  EXPECT_NO_THROW(parser.matchings());    //??
  vector<Term *> terms = parser.getTerms();
  EXPECT_EQ(2, terms.size());
  EXPECT_EQ("1", terms[0]->symbol());
  EXPECT_EQ("2", terms[1]->symbol());
   Node * et = parser.expressionTree();
   EXPECT_FALSE(et->evaluate());
}

TEST_F(ParserTest, TwoTermsMatching) {
  Scanner scanner("X=1, Y=2.");
  Parser parser(scanner);
  parser.matchings();
  vector<Term *> terms = parser.getTerms();
  EXPECT_EQ(4, terms.size());
  EXPECT_EQ("X", terms[0]->symbol());
  EXPECT_EQ("1", terms[1]->symbol());
  EXPECT_EQ("Y", terms[2]->symbol());
  EXPECT_EQ("2", terms[3]->symbol());
    Node * et = parser.expressionTree();
     EXPECT_TRUE(et->evaluate());
     EXPECT_EQ(COMMA, et->payload);
     EXPECT_EQ("1", terms[0]->value());
     EXPECT_EQ("2", terms[2]->value());
}

TEST_F(ParserTest, ThreeTermsMatching) {
  Scanner scanner("X=1, Y=2, Z=3.");
  Parser parser(scanner);
  parser.matchings();
  vector<Term *> terms = parser.getTerms();
  EXPECT_EQ(6, terms.size());
  EXPECT_EQ("X", terms[0]->symbol());
  EXPECT_EQ("1", terms[1]->symbol());
  EXPECT_EQ("Y", terms[2]->symbol());
  EXPECT_EQ("2", terms[3]->symbol());

   Node * et = parser.expressionTree();
  EXPECT_TRUE(et->evaluate());
  EXPECT_EQ(COMMA, et->payload);
  EXPECT_EQ(EQUALITY, et->left->payload);
  EXPECT_EQ(COMMA, et->right->payload);
  EXPECT_EQ(EQUALITY, et->right->left->payload);
  EXPECT_EQ(EQUALITY, et->right->right->payload);

  EXPECT_EQ("1", terms[0]->value());
  EXPECT_EQ("2", terms[2]->value());
  EXPECT_EQ("3", terms[4]->value());
}

TEST_F(ParserTest, TwoVariableMatching2) {
  Scanner scanner("X=1, X=Y.");
  Parser parser(scanner);
  parser.matchings();
  vector<Term *> terms = parser.getTerms();
  EXPECT_EQ(4, terms.size());
  EXPECT_EQ("X", terms[0]->symbol());
  EXPECT_EQ("1", terms[1]->symbol());
  EXPECT_EQ("X", terms[2]->symbol());
  EXPECT_EQ("Y", terms[3]->symbol());

   Node * et = parser.expressionTree();
   EXPECT_TRUE(et->evaluate());
   EXPECT_EQ("1", terms[0]->value());
   EXPECT_EQ("1", terms[2]->value());
}

TEST_F(ParserTest, TwoVariableMatching3) {
  Scanner scanner("X=Y, X=1.");
  Parser parser(scanner);
  parser.matchings();
  vector<Term *> terms = parser.getTerms();
  EXPECT_EQ(4, terms.size());
  EXPECT_EQ("X", terms[0]->symbol());
  EXPECT_EQ("Y", terms[1]->symbol());
  EXPECT_EQ("X", terms[2]->symbol());
  EXPECT_EQ("1", terms[3]->symbol());

  Node * et = parser.expressionTree();
   EXPECT_TRUE(et->evaluate());
   EXPECT_EQ("1", terms[0]->value());
   EXPECT_EQ("1", terms[1]->value());
}

TEST_F(ParserTest, VarAStructOfVar) {
  Scanner scanner("X=s(Y).");
  Parser parser(scanner);
  parser.matchings();

  vector<Term *> terms = parser.getTerms();
  EXPECT_EQ(2, terms.size());

  EXPECT_EQ("X", terms[0]->symbol());
  EXPECT_EQ("X", terms[0]->value());
  EXPECT_EQ("s(Y)", terms[1]->symbol());

  Node * et = parser.expressionTree();
  EXPECT_EQ(EQUALITY, et->payload);
  EXPECT_EQ(TERM, et->left->payload);
  EXPECT_EQ(TERM, et->right->payload);
  EXPECT_EQ("X", et->left->term->symbol());
  EXPECT_EQ("s(Y)", et->right->term->symbol());
  EXPECT_TRUE(et->evaluate());
}

// TEST_F(ParserTest, TwoVariableMatching4) {
//   Scanner scanner("X=s(Y), Y=1.");
//   Parser parser(scanner);
//   parser.matchings();
//   vector<Term *> terms = parser.getTerms();
//   EXPECT_EQ(4, terms.size());
//   EXPECT_EQ("X", terms[0]->symbol());
//   EXPECT_EQ("X", terms[0]->value());
//   EXPECT_EQ("s(Y)", terms[1]->symbol());
//   EXPECT_EQ("Y", terms[2]->symbol());
//   EXPECT_EQ("1", terms[3]->symbol());
//
//   Node * et = parser.expressionTree();
//   EXPECT_TRUE(et->evaluate());
//   EXPECT_EQ(COMMA, et->payload);
//   EXPECT_EQ(EQUALITY, et->left->payload);
//   EXPECT_EQ("X", et->left->left->term->symbol());
//   EXPECT_EQ("s(Y)", et->left->right->term->symbol());
//   EXPECT_EQ("s(Y)", terms[1]->symbol());
//   EXPECT_EQ(EQUALITY, et->right->payload);
//   EXPECT_EQ("Y", et->right->left->term->symbol());
//   EXPECT_EQ("1", et->right->right->term->symbol());
//
//   EXPECT_EQ("X", terms[0]->symbol());
//   EXPECT_EQ("s(1)", terms[0]->value());
//   EXPECT_EQ("s(1)", terms[1]->value());
//   EXPECT_EQ("Y", terms[2]->symbol());
//   EXPECT_EQ("1", terms[2]->value());
// }
//
TEST_F(ParserTest, ConjTwoMatchingFailure) {
  Scanner scanner("X=1, X=2.");
  Parser parser(scanner);
  parser.matchings();
  vector<Term *> terms = parser.getTerms();
  EXPECT_EQ(4, terms.size());
  EXPECT_EQ("X", terms[0]->symbol());
  EXPECT_EQ("1", terms[1]->symbol());
  EXPECT_EQ("X", terms[2]->symbol());
  EXPECT_EQ("2", terms[3]->symbol());

  Node * et = parser.expressionTree();
  EXPECT_EQ(COMMA, et->payload);
  EXPECT_EQ(EQUALITY, et->left->payload);
  EXPECT_EQ(EQUALITY, et->right->payload);
  EXPECT_EQ("X", et->left->left->term->symbol());
  EXPECT_EQ("1", et->left->right->term->symbol());
  EXPECT_EQ("X", et->right->left->term->symbol());
  EXPECT_EQ("2", et->right->right->term->symbol());

  EXPECT_FALSE(et->evaluate());
}

TEST_F(ParserTest, DisjTwoMatchingSuccess) {
  Scanner scanner("X=1; X=2.");
  Parser parser(scanner);
  parser.matchings();
  vector<Term *> terms = parser.getTerms();
  EXPECT_EQ(4, terms.size());
  EXPECT_EQ("X", terms[0]->symbol());
  EXPECT_EQ("1", terms[1]->symbol());
  EXPECT_EQ("X", terms[2]->symbol());
  EXPECT_EQ("2", terms[3]->symbol());

   Node * et = parser.expressionTree();
   EXPECT_EQ(SEMICOLON, et->payload);
   EXPECT_EQ(EQUALITY, et->left->payload);
   EXPECT_EQ(EQUALITY, et->right->payload);
   EXPECT_EQ("X", et->left->left->term->symbol());
  EXPECT_EQ("1", et->left->right->term->symbol());
   EXPECT_EQ("X", et->right->left->term->symbol());
    EXPECT_EQ("2", et->right->right->term->symbol());
    
   EXPECT_TRUE(et->evaluate());
   EXPECT_EQ("1", terms[0]->value());
   EXPECT_EQ("2", terms[2]->value());
}

// TEST_F(ParserTest, MatchingSuccess) {
//   Scanner scanner("X=1; X=2, Y=s(s(X)).");
//   Parser parser(scanner);
//   parser.matchings();
//   vector<Term *> terms = parser.getTerms();
//    Node * et = parser.expressionTree();
//    EXPECT_TRUE(et->evaluate());
  // EXPECT_EQ("1", terms[0]->value());
  // EXPECT_EQ("2", terms[2]->value());
  // EXPECT_EQ("s(s(2))", terms[4]->value());
//}

#endif
