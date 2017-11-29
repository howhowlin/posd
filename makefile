all: hw6

hw6:  Number.o Atom.o Variable.o List.o mainScanner.o

ifeq (${OS}, Windows_NT)
	g++ -o hw6 mainScanner.o Atom.o Number.o Variable.o List.o -lgtest
else
	g++ -o hw6 mainScanner.o Atom.o Number.o Variable.o List.o -lgtest -lpthread
endif

mainScanner.o: mainScanner.cpp utParser.h scanner.h parser.h struct.h
	g++ -std=gnu++0x -c mainScanner.cpp



Number.o: number.h Number.cpp
	g++ -std=gnu++0x -c Number.cpp

Variable.o: variable.h Variable.cpp
	g++ -std=gnu++0x -c Variable.cpp

Atom.o: atom.h Atom.cpp
	g++ -std=gnu++0x -c Atom.cpp

List.o: list.h List.cpp
	g++ -std=gnu++0x -c List.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw6
endif
