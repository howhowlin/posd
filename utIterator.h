#ifndef UTITERATOR_H
#define UTITERATOR_H

#include "number.h"
#include "variable.h"
#include "iterator.h"
#include "parser.h"

TEST(iterator, first) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    Struct s(Atom("s"), { &one, &t, &Y });
    //StructIterator it(&s);
    Iterator<Term*> *itStruct = s.createIterator();

    // Iterator& itStruct = it;
    // ASSERT_EQ(it.first()->symbol());
    itStruct->first();

    ASSERT_EQ("1", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("t(X, 2)", itStruct->currentItem()->symbol());
    ASSERT_FALSE(itStruct->isDone());
    itStruct->next();
    ASSERT_EQ("Y", itStruct->currentItem()->symbol());
    itStruct->next();
    ASSERT_TRUE(itStruct->isDone());
}

TEST(iterator, nested_iterator) {
  Number one(1);
  Variable X("X");
  Variable Y("Y");
  Number two(2);
  Struct t(Atom("t"), { &X, &two });
  Struct s(Atom("s"), { &one, &t, &Y });
  StructIterator it(&s);
  it.first();
  it.next();
  Struct *s2 = dynamic_cast<Struct *>(it.currentItem());

  StructIterator it2(s2);
  it2.first();
  ASSERT_EQ("X", it2.currentItem()->symbol());
  ASSERT_FALSE(it2.isDone());
  it2.next();
  ASSERT_EQ("2", it2.currentItem()->symbol());
  ASSERT_FALSE(it2.isDone());
  it2.next();
  ASSERT_TRUE(it2.isDone());
}

TEST(iterator, firstList) {
    Number one(1);
    Variable X("X");
    Variable Y("Y");
    Number two(2);
    Struct t(Atom("t"), { &X, &two });
    List l({ &one, &t, &Y });
    Iterator<Term*> *itList = l.createIterator();
     itList->first();
     ASSERT_EQ("1", itList->currentItem()->symbol());
     ASSERT_FALSE(itList->isDone());
     itList->next();
     ASSERT_EQ("t(X, 2)", itList->currentItem()->symbol());
     ASSERT_FALSE(itList->isDone());
     itList->next();
     ASSERT_EQ("Y", itList->currentItem()->symbol());
     itList->next();
     ASSERT_TRUE(itList->isDone());
}

TEST(iterator, NullIterator){
  Number one(1);
  NullIterator nullIterator(&one);
  nullIterator.first();
  ASSERT_TRUE(nullIterator.isDone());
  Iterator<Term*> * it = one.createIterator();
  it->first();
  ASSERT_TRUE(it->isDone());
}

TEST(iterator, BFS_Struct_1){
  Atom bun("bun");
  Atom beefPatty("beefPatty");
  Atom shreddedLettuce("shreddedLettuce");
  Atom pickleSlice1("pickleSlice1");
  Atom pickleSlice2("pickleSlice2");
  Atom onion1("onion1");
  Atom onion2("onion2");
  Atom coke("coke");
  Atom fries1("fries1");
  Atom fries2("fries2");
  List l({&pickleSlice1, &pickleSlice2});
  List u({&onion1, &onion2});
  List v({&fries1, &fries2});
  Struct bigMac(Atom("bigMac"),{&bun, &beefPatty, &shreddedLettuce, &l, &u});
  Struct combo1(Atom("combo1"),{&bigMac, &coke, &v});
  Iterator<Term*> *BFSIt = combo1.createBFSIterator();
  BFSIt->first();
  ASSERT_EQ("bigMac(bun, beefPatty, shreddedLettuce, [pickleSlice1, pickleSlice2], [onion1, onion2])", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("coke", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[fries1, fries2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("bun", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("beefPatty", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("shreddedLettuce", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[pickleSlice1, pickleSlice2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[onion1, onion2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("fries1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("fries2", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("pickleSlice1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("pickleSlice2", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("onion1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("onion2", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_TRUE(BFSIt->isDone());
}
TEST(iterator, BFS_Struct_2){
  Atom bun("bun");
  Atom beefPatty("beefPatty");
  Atom shreddedLettuce("shreddedLettuce");
  Atom pickleSlice1("pickleSlice1");
  Atom pickleSlice2("pickleSlice2");
  Atom onion1("onion1");
  Atom onion2("onion2");
  Atom coke("coke");
  Atom fries1("fries1");
  Atom fries2("fries2");
  List l({&pickleSlice1, &pickleSlice2});
  List u({&onion1, &onion2});
  List v({&fries1, &fries2});
  Struct bigMac(Atom("bigMac"),{&bun, &beefPatty, &shreddedLettuce, &l, &u});
  Struct combo1(Atom("combo1"),{&v, &bigMac, &coke});
  Iterator<Term*> *BFSIt = combo1.createBFSIterator();
  BFSIt->first();
  ASSERT_EQ("[fries1, fries2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("bigMac(bun, beefPatty, shreddedLettuce, [pickleSlice1, pickleSlice2], [onion1, onion2])", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("coke", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("fries1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("fries2", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("bun", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("beefPatty", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("shreddedLettuce", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[pickleSlice1, pickleSlice2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[onion1, onion2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("pickleSlice1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("pickleSlice2", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("onion1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("onion2", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_TRUE(BFSIt->isDone());
}
TEST(iterator, BFS_List_1){
  Atom bun("bun");
  Atom beefPatty("beefPatty");
  Atom shreddedLettuce("shreddedLettuce");
  Atom pickleSlice1("pickleSlice1");
  Atom pickleSlice2("pickleSlice2");
  Atom onion1("onion1");
  Atom onion2("onion2");
  Atom coke("coke");
  Atom fries1("fries1");
  Atom fries2("fries2");
  List l({&pickleSlice1, &pickleSlice2});
  List u({&onion1, &onion2});
  List v({&fries1, &fries2});
  Struct bigMac(Atom("bigMac"),{&bun, &beefPatty, &shreddedLettuce, &l, &u});
  List ll({&bigMac, &coke, &v});
  Iterator<Term*> *BFSIt = ll.createBFSIterator();
  BFSIt->first();
  ASSERT_EQ("bigMac(bun, beefPatty, shreddedLettuce, [pickleSlice1, pickleSlice2], [onion1, onion2])", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("coke", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[fries1, fries2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("bun", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("beefPatty", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("shreddedLettuce", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[pickleSlice1, pickleSlice2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[onion1, onion2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("fries1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("fries2", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("pickleSlice1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("pickleSlice2", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("onion1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("onion2", BFSIt->currentItem()->symbol());
  BFSIt->next();

  ASSERT_TRUE(BFSIt->isDone());
}
TEST(iterator, BFS_List_2){
  Atom bun("bun");
  Atom beefPatty("beefPatty");
  Atom shreddedLettuce("shreddedLettuce");
  Atom pickleSlice1("pickleSlice1");
  Atom pickleSlice2("pickleSlice2");
  Atom onion1("onion1");
  Atom onion2("onion2");
  Atom coke("coke");
  Atom fries1("fries1");
  Atom fries2("fries2");
  List l({&pickleSlice1, &pickleSlice2});
  List u({&onion1, &onion2});
  List v({&fries1, &fries2});
  Struct bigMac(Atom("bigMac"),{&bun, &beefPatty, &shreddedLettuce, &l, &u});
  List ll({&coke, &v, &bigMac});
  Iterator<Term*> *BFSIt = ll.createBFSIterator();
  BFSIt->first();
  ASSERT_EQ("coke", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[fries1, fries2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("bigMac(bun, beefPatty, shreddedLettuce, [pickleSlice1, pickleSlice2], [onion1, onion2])", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("fries1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("fries2", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("bun", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("beefPatty", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("shreddedLettuce", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[pickleSlice1, pickleSlice2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("[onion1, onion2]", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("pickleSlice1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("pickleSlice2", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("onion1", BFSIt->currentItem()->symbol());
  BFSIt->next();
  ASSERT_EQ("onion2", BFSIt->currentItem()->symbol());
  BFSIt->next();

  ASSERT_TRUE(BFSIt->isDone());
}

TEST(iterator, DFS_Struct_1){
  Atom bun("bun");
  Atom beefPatty("beefPatty");
  Atom shreddedLettuce("shreddedLettuce");
  Atom pickleSlice1("pickleSlice1");
  Atom pickleSlice2("pickleSlice2");
  Atom onion1("onion1");
  Atom onion2("onion2");
  Atom coke("coke");
  Atom fries1("fries1");
  Atom fries2("fries2");
  List l({&pickleSlice1, &pickleSlice2});
  List u({&onion1, &onion2});
  List v({&fries1, &fries2});
  Struct bigMac(Atom("bigMac"),{&bun, &beefPatty, &shreddedLettuce, &l, &u});
  Struct combo1(Atom("combo1"),{&bigMac, &coke, &v});
  Iterator<Term*> *DFSIt = combo1.createDFSIterator();
  DFSIt->first();
  ASSERT_EQ("bigMac(bun, beefPatty, shreddedLettuce, [pickleSlice1, pickleSlice2], [onion1, onion2])", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("bun", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("beefPatty", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("shreddedLettuce", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[pickleSlice1, pickleSlice2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("pickleSlice1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("pickleSlice2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[onion1, onion2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("onion1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("onion2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("coke", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[fries1, fries2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("fries1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("fries2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_TRUE(DFSIt->isDone());
}
TEST(iterator, DFS_Struct_2){
  Atom bun("bun");
  Atom beefPatty("beefPatty");
  Atom shreddedLettuce("shreddedLettuce");
  Atom pickleSlice1("pickleSlice1");
  Atom pickleSlice2("pickleSlice2");
  Atom onion1("onion1");
  Atom onion2("onion2");
  Atom coke("coke");
  Atom fries1("fries1");
  Atom fries2("fries2");
  List l({&pickleSlice1, &pickleSlice2});
  List u({&onion1, &onion2});
  List v({&fries1, &fries2});
  Struct bigMac(Atom("bigMac"),{&bun, &beefPatty, &shreddedLettuce, &l, &u});
  Struct combo1(Atom("combo1"),{&v, &bigMac, &coke});
  Iterator<Term*> *DFSIt = combo1.createDFSIterator();
  DFSIt->first();
  ASSERT_EQ("[fries1, fries2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("fries1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("fries2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("bigMac(bun, beefPatty, shreddedLettuce, [pickleSlice1, pickleSlice2], [onion1, onion2])", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("bun", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("beefPatty", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("shreddedLettuce", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[pickleSlice1, pickleSlice2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("pickleSlice1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("pickleSlice2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[onion1, onion2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("onion1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("onion2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("coke", DFSIt->currentItem()->symbol());
  DFSIt->next();

  ASSERT_TRUE(DFSIt->isDone());

}
TEST(iterator, DFS_List_1){
  Atom bun("bun");
  Atom beefPatty("beefPatty");
  Atom shreddedLettuce("shreddedLettuce");
  Atom pickleSlice1("pickleSlice1");
  Atom pickleSlice2("pickleSlice2");
  Atom onion1("onion1");
  Atom onion2("onion2");
  Atom coke("coke");
  Atom fries1("fries1");
  Atom fries2("fries2");
  List l({&pickleSlice1, &pickleSlice2});
  List u({&onion1, &onion2});
  List v({&fries1, &fries2});
  Struct bigMac(Atom("bigMac"),{&bun, &beefPatty, &shreddedLettuce, &l, &u});
  List ll({&bigMac, &coke, &v});
  Iterator<Term*> *DFSIt = ll.createDFSIterator();
  DFSIt->first();
  ASSERT_EQ("bigMac(bun, beefPatty, shreddedLettuce, [pickleSlice1, pickleSlice2], [onion1, onion2])", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("bun", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("beefPatty", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("shreddedLettuce", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[pickleSlice1, pickleSlice2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("pickleSlice1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("pickleSlice2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[onion1, onion2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("onion1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("onion2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("coke", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[fries1, fries2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("fries1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("fries2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_TRUE(DFSIt->isDone());

}
TEST(iterator, DFS_List_2){
  Atom bun("bun");
  Atom beefPatty("beefPatty");
  Atom shreddedLettuce("shreddedLettuce");
  Atom pickleSlice1("pickleSlice1");
  Atom pickleSlice2("pickleSlice2");
  Atom onion1("onion1");
  Atom onion2("onion2");
  Atom coke("coke");
  Atom fries1("fries1");
  Atom fries2("fries2");
  List l({&pickleSlice1, &pickleSlice2});
  List u({&onion1, &onion2});
  List v({&fries1, &fries2});
  Struct bigMac(Atom("bigMac"),{&bun, &beefPatty, &shreddedLettuce, &l, &u});
  List ll({&coke, &v, &bigMac});
  Iterator<Term*> *DFSIt = ll.createDFSIterator();
  DFSIt->first();
  ASSERT_EQ("coke", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[fries1, fries2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("fries1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("fries2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("bigMac(bun, beefPatty, shreddedLettuce, [pickleSlice1, pickleSlice2], [onion1, onion2])", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("bun", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("beefPatty", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("shreddedLettuce", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[pickleSlice1, pickleSlice2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("pickleSlice1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("pickleSlice2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("[onion1, onion2]", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("onion1", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_EQ("onion2", DFSIt->currentItem()->symbol());
  DFSIt->next();
  ASSERT_TRUE(DFSIt->isDone());
}



#endif
