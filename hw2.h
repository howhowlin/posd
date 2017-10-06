#ifndef HW2_H
#define HW2_H

#include "variable.h"
#include "atom.h"
#include "number.h"

//test Number.value()
TEST (Number, ctor) {
  Number X(1);
  ASSERT_EQ("1",X.value());
}

// test Number.symbol()
TEST (Number, symbol) {
  Number X("X");
  ASSERT_EQ("X",X.symbol());
}

//?- 25 = 25.
// true.
TEST (Number, matchSuccess) {
  Number X(25);
  Number Y(25);
  EXPECT_TRUE(X.match(Y));
}
//?- 25 = 0.
// false.
TEST (Number, matchFailureDiffValue) {
  Number X(25);
  Number Y(0);
  EXPECT_FALSE(X.match(Y));
}

// ?- 25 = tom.
//false.
TEST (Number, matchFailureDiffConstant) {
 Number X(25);
 Atom   Y("tom");
 EXPECT_FALSE(X.match(Y));
}

//?- 25 = X.
// true.
TEST (Number, matchSuccessToVar) {
 Number X(25);
 Variable Y("X");
 EXPECT_TRUE(X.match(Y));
}

//
// //?- tom = 25.
// false.
TEST (Atom, matchFailureDiffConstant) {
  Atom X("tom");
  Number Y(25);
  EXPECT_FALSE(X.match(Y));
}
//
// ?- tom = X.
// X = tom.
TEST (Atom, matchSuccessToVar) {
  Atom     X("tom");
  Variable Y("X");
  ASSERT_TRUE(X.match(Y));
}
//
// // ?- X = tom, tom = X.
// // X = tom.
TEST (Atom, matchSuccessToVarInstantedToDiffConstant) {
  Variable  X("X");
  Atom      Y("tom");
  ASSERT_TRUE(X.match(Y));
  ASSERT_TRUE(Y.match(X));
}
//
// // ?- X = jerry, tom = X.
// // false.
TEST (Atom, matchFailureToVarInstantedToDiffConstant) {
  Variable  X("X");
  Atom      Y("jerry");
  Atom      Z("tom");
  ASSERT_TRUE(X.match(Y));
  ASSERT_FALSE(Z.match(X));
}
//
// // ?- X = 5.
// // X = 5.
TEST (Variable, matchSuccessToNumber) {
    Variable X("X");
    Number   Y(5);
    ASSERT_TRUE(X.match(Y));
}
//
// // ?- X = 25, X = 100.
// // false.
TEST (Variable, matchFailureToTwoDiffNumbers) {
   Variable X("X");
   Number   Y(25);
   Number   Z(100);
   ASSERT_TRUE(X.match(Y));
   ASSERT_FALSE(Y.match(Z));
}
//
// // ?- X = tom, X = 25.
// // false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber) {
    Variable X("X");
    Atom     Y("tom");
    Number   Z(25);
    ASSERT_TRUE(X.match(Y));
    ASSERT_FALSE(Y.match(Z));
}
// //?- tom = X, 25 = X.
// // false.
TEST (Variable, matchSuccessToAtomThenFailureToNumber2) {
  Atom     X("tom");
  Variable Y("X");
  Number   Z(25);
  ASSERT_TRUE(X.match(Y));  //comin true
  ASSERT_FALSE(Z.match(Y));
}
// //?- X = tom, X = tom.
// // true.
TEST(Variable, reAssignTheSameAtom){
   Variable X("X");
   Atom     Y("tom");
   ASSERT_TRUE(X.match(Y));
   ASSERT_TRUE(X.match(Y));
}
#endif
