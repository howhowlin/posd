all: hw2



hw2: MainTerm.o Number.o Variable.o  Atom.o
	 g++ -o hw2 MainTerm.o Number.o Variable.o  Atom.o -lgtest -lpthread

MainTerm.o: MainTerm.cpp hw2.h
	 g++ -std=gnu++0x -c MainTerm.cpp

Number.o:number.h Number.cpp
	g++ -std=gnu++0x  -c Number.cpp

Variable.o:variable.h Variable.cpp
	g++ -std=gnu++0x  -c Variable.cpp

Atom.o:atom.h Atom.cpp
	g++ -std=gnu++0x  -c Atom.cpp

clean:
	rm -f *.o madRace utAtom
stat:
	wc *.h *.cpp
