all: begin

begin:	CPUProgram.o _mainTester.o
	g++ CPUProgram.o _mainTester.o -o exe

CPUProgram.o: CPUProgram.cpp
	g++ -std=c++11 -c CPUProgram.cpp

_mainTester.o: _mainTester.cpp
	g++ -std=c++11 -c _mainTester.cpp
	
clean:
	rm *.o exe

