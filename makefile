all: hw2

hw2: MainTerm.o Number.o Variable.o  Atom.o

ifeq (${OS}, Windows_NT)
		g++ -o hw2 MainTerm.o Atom.o Number.o Variable.o -lgtest
else
		g++ -o hw2 MainTerm.o Atom.o Number.o Variable.o -lgtest -lpthread
endif



MainTerm.o: MainTerm.cpp utTerm.h
	 g++ -std=gnu++0x -c MainTerm.cpp

Number.o:number.h Number.cpp
	g++ -std=gnu++0x  -c Number.cpp

Variable.o:variable.h Variable.cpp
	g++ -std=gnu++0x  -c Variable.cpp

Atom.o:atom.h Atom.cpp
	g++ -std=gnu++0x  -c Atom.cpp


clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
