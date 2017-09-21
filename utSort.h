#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

using namespace std;

TEST(Sort, sortByIncreasingPerimeter) {
	Sort a;

	Circle cir0(0, 0, 1);
	Circle cir1(1, 1, 2);
	Circle cir2(2, 2, 3);
	std::list<Shape *>  shapeList;
	std::list<Shape *> ::iterator it;
	shapeList.push_back(&cir0);
	shapeList.push_back(&cir1);
	shapeList.push_back(&cir2);

	a.sortByIncreasingPerimeter(&shapeList);

	it = shapeList.begin();
	ASSERT_EQ(&cir0, *it);
	it++;
	ASSERT_EQ(&cir1, *it);
	it++;
	ASSERT_EQ(&cir2, *it);

}

TEST (Sort, sortByDecreasingPerimeter) {
	Sort a;
	Circle cir0(0, 0, 1);
	Circle cir1(1, 1, 2);
	Circle cir2(2, 2, 3);
	std::list<Shape *>   shapeList;
	std::list<Shape *> ::iterator it;
	shapeList.push_back(&cir0);
	shapeList.push_back(&cir1);
	shapeList.push_back(&cir2);
	a.sortByDecreasingPerimeter(&shapeList);
	it = shapeList.begin();
	ASSERT_EQ(&cir2, *it);
	it++;
	ASSERT_EQ(&cir1, *it);
	it++;
	ASSERT_EQ(&cir0, *it);
}

TEST (Sort, sortByIncreasingArea) {
	Sort a;
	Circle cir0(0, 0, 1);
	Circle cir1(1, 1, 2);
	Circle cir2(2, 2, 3);
	std::list<Shape *>  shapeList;
	std::list<Shape *> ::iterator it;
	shapeList.push_back(&cir0);
	shapeList.push_back(&cir1);
	shapeList.push_back(&cir2);
	a.sortByIncreasingArea(&shapeList);
	it = shapeList.begin();
	ASSERT_EQ(&cir0, *it);
	it++;
	ASSERT_EQ(&cir1, *it);
	it++;
	ASSERT_EQ(&cir2, *it);

}

TEST (Sort, sortByDecreasingArea) {
	Sort a;
	Circle cir0(0, 0, 1);
	Circle cir1(1, 1, 2);
	Circle cir2(2, 2, 3);
	std::list<Shape *> shapeList;
	std::list<Shape *> ::iterator it;
	shapeList.push_back(&cir0);
	shapeList.push_back(&cir1);
	shapeList.push_back(&cir2);
	a.sortByDecreasingArea(&shapeList);
	it = shapeList.begin();
	ASSERT_EQ(&cir2, *it);
	it++;
	ASSERT_EQ(&cir1, *it);
	it++;
	ASSERT_EQ(&cir0, *it);

}

TEST (Sort, sortByIncreasingCompactness) {
	Sort a;
	Circle cir0(0, 0, 1);
	Circle cir1(1, 1, 2);
	Circle cir2(2, 2, 3);
	std::list<Shape *>   shapeList;
	std::list<Shape *> ::iterator it;
	shapeList.push_back(&cir0);
	shapeList.push_back(&cir1);
	shapeList.push_back(&cir2);
	a.sortByIncreasingCompactness(&shapeList);
	it = shapeList.begin();
	ASSERT_EQ(&cir2, *it);
	it++;
	ASSERT_EQ(&cir1, *it);
	it++;
	ASSERT_EQ(&cir0, *it);
}

#endif
