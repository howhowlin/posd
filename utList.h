#ifndef UTLIST_H
#define UTLIST_H
#include <string>
using std::string;
#include <iostream>
#include "list.h"
#include "struct.h"
#include "atom.h"
#include "number.h"
#include "variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST (List, constructor) {
  vector<Term *> args = {};
  List l(args);
  EXPECT_EQ("[]",l.symbol());
}

// Given there are two perfect Numbers: 8128, 496
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128, 496]"
TEST(List, Numbers) {
    Number a(8128),b( 496);
    vector<Term *> args = {&a, &b};
    List l(args);
    EXPECT_EQ("[8128, 496]",l.symbol());
    //把number a的直和number的直抓進來
}

// // Given there are two atoms: "terence_tao", "alan_mathison_turing"
// // When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
   Atom a("terence_tao"),b("alan_mathison_turing");
   vector<Term *> args = {&a, &b};
   List l(args);
   EXPECT_EQ("[terence_tao, alan_mathison_turing]",l.symbol());
}

// // Given there are two variables: X, Y
// // When create a new list with the variables
// // Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
   Variable a("X"),b("Y");
   vector<Term *> args = {&a, &b};
   List l(args);
   EXPECT_EQ("[X, Y]",l.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
    Number   a(496);
    Variable b("X");
    Atom     c("terence_tao");
    Atom     tom("tom");
    vector<Term *> args = {&a, &b,&c};
    List   l(args);
    EXPECT_FALSE(tom.match(l));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
  Number   a(496);
  Variable b("X");
  Atom     c("terence_tao");
  Number     Number(8128);
  vector<Term *> args = {&a, &b,&c};
  List   l(args);
  EXPECT_FALSE(Number.match(l));
}

// // ?- s(X) = [496, X, terence_tao].
// // false.
TEST(List, matchToStructShouldFail) {
  Variable X("X");
  std::vector<Term *> v = {&X};
  Struct s(Atom("s"), v);
  ASSERT_EQ("s(X)",s.symbol());

  Number   a(496);
  Variable b("X");
  Atom     c("terence_tao");
  vector<Term *> args = {&a, &b,&c};
  List   l(args);
  EXPECT_FALSE(s.match(l));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
  Variable Y("Y");
  Number   a(496);
  Variable b("X");
  Atom     c("terence_tao");
  vector<Term *> args = {&a, &b,&c};
  List   l(args);
  EXPECT_TRUE(Y.match(l));
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
  Variable Y("X");
  Number   a(496);
  Variable b("X");
  Atom     c("terence_tao");
  vector<Term *> args = {&a, &b,&c};
  List   l(args);
  EXPECT_TRUE(Y.match(l));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
  Number   a(496);
  Variable b("X");
  Atom     c("terence_tao");
  vector<Term *> args = {&a, &b,&c};
  List   l1(args);    //[496, X, terence_tao]

  Number   d(496);
  Variable e("X");
  Atom     f("terence_tao");
  vector<Term *> args1 ={&d,&e,&f};
  List   l2(args1);   //[496, X, terence_tao]

  EXPECT_TRUE(l1.match(l2));      //還沒寫好 match 只會一直回傳true
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
  Number   a(496);
  Variable b("X");
  Atom     c("terence_tao");
  vector<Term *> args = {&a, &b,&c};
  List   l1(args);    //[496, X, terence_tao]

  Number   d(496);
  Variable e("Y");
  Atom     f("terence_tao");
  vector<Term *> args1 ={&d,&e,&f};
  List   l2(args1);   //[496, X, terence_tao]

  EXPECT_TRUE(l1.match(l2));

}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
  Number   a(496);
  Variable b("X");
  Atom     c("terence_tao");
  vector<Term *> args = {&a, &b,&c};
  List   l1(args);    //[496, X, terence_tao]

  Number   d(496);
  Number   e(8128);
  Atom     f("terence_tao");
  vector<Term *> args1 ={&d,&e,&f};
  List   l2(args1);   //[496, X, terence_tao]
  EXPECT_TRUE(l1.match(l2));
  EXPECT_EQ("8128",b.value());
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
  Variable X("X");
  Atom  alan_mathison_turing(" alan_mathison_turing"); //space problem
  EXPECT_TRUE(X.match(alan_mathison_turing)); // X = alan_mathison_turing.
  EXPECT_EQ(" alan_mathison_turing",X.value());

  Variable Y("Y");
  Number   a(496);
  Atom     c("terence_tao");
  vector<Term *> args = {&a, &X,&c};
  List   l1(args);
  EXPECT_TRUE(Y.match(l1)); //Y = [496, X, terence_tao]

  EXPECT_EQ("[496, alan_mathison_turing, terence_tao]",Y.value());

}

// // Example:
// // ?- [first, second, third] = [H|T].
// // H = first, T = [second, third].
// TEST(List, headAndTailMatching1) {
//   // Atom f("first"), s("second"), t("third");
//   // vector<Term *> args = {&f, &s, &t};
//   // List l(args);
//   //
//   // EXPECT_EQ(string("first"), l.head()->symbol());
//   // EXPECT_EQ(string("[second, third]"), l.tail()->value());
// }
//
// // Example:
// // ?- [first, second, third] = [first, H|T].
// // H = second, T = [third].
// TEST(List, headAndTailMatching2) {
//   // Atom f("first"), s("second"), t("third");
//   // vector<Term *> args = {&f, &s, &t};
//   // List l(args);
//   //
//   // EXPECT_EQ(string("second"), l.tail()->head()->value());
//   // EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
// }
//
// // ?- [[first], second, third] = [H|T].
// // H = [first], T = [second, third].
// TEST(List, headAndTailMatching3) {
//
// }
//
// // ?- [first, second, third] = [first, second, H|T].
// // H = third, T = [].
// TEST(List, headAndTailMatching4) {
//
// }
//
// // Given there is a empty list
// // When client still want to get the head of list
// // Then it should throw a string: "Accessing head in an empty list" as an exception.
// TEST (List, emptyExecptionOfHead) {
//
// }
//
// // Given there is a empty list
// // When client still want to get the head of list
// // Then it should throw a string: "Accessing tail in an empty list" as an exception.
// TEST (List, emptyExecptionOfTail) {
//
// }
#endif
