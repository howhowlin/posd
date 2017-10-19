all: hw3

hw3:  mainAtom.o Number.o Atom.o Variable.o

ifeq (${OS}, Windows_NT)
	g++ -o hw3  mainAtom.o Atom.o Number.o Variable.o -lgtest
else
	g++ -o hw3  mainAtom.o Atom.o Number.o Variable.o -lgtest -lpthread
endif

mainAtom.o: mainAtom.cpp utVariable.h utStruct.h
		g++ -std=gnu++0x -c mainAtom.cpp

Number.o: number.h Number.cpp
		g++ -std=gnu++0x -c Number.cpp

Atom.o: atom.h Atom.cpp
	g++ -std=gnu++0x -c Atom.cpp

Variable.o: variable.h Variable.cpp
	g++ -std=gnu++0x -c Variable.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif
