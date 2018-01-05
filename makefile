all: hw8

hw8: mainScanner.o Number.o Atom.o  List.o Struct.o

ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainScanner.o Atom.o Number.o  List.o Struct.o  -lgtest
else
	g++ -o hw8 mainScanner.o Atom.o Number.o  List.o Struct.o -lgtest -lpthread
endif

mainScanner.o: mainScanner.cpp utScanner.h utParser.h scanner.h parser.h utIterator.h iterator.h
				g++ -std=gnu++0x -c mainScanner.cpp

Number.o: number.h Number.cpp
		g++ -std=gnu++0x -c Number.cpp

Atom.o: atom.h Atom.cpp
	g++ -std=gnu++0x -c Atom.cpp



Struct.o: Struct.cpp struct.h
	g++ -std=gnu++0x -c Struct.cpp

List.o: list.h List.cpp
	g++ -std=gnu++0x -c List.cpp



clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw8
endif
