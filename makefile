all: hw2



hw2: MainTerm.o Number.o Variable.o  Atom.o
	 g++ -o hw2 MainTerm.o Number.o Variable.o  Atom.o -lgtest -lpthread

MainTerm.o: MainTerm.cpp hw2.h
	 g++ -std=c++11 -c MainTerm.cpp

Number.o:number.h Number.cpp
	g++ -std=c++11 -c Number.cpp

Variable.o:variable.h Variable.cpp
	g++ -std=c++11 -c Variable.cpp

Atom.o:atom.h Atom.cpp
	g++ -std=c++11 -c Atom.cpp

clean:
	rm -f *.o madRace utAtom
stat:
	wc *.h *.cpp
