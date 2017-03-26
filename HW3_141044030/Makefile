all: begin

begin: driver.o CPU.o CPUProgram.o
	  g++ driver.o CPU.o CPUProgram.o -o exe

driver.o: driver.cpp
	g++ -std=c++11 -c driver.cpp

CPU.o: CPU.cpp
	g++ -std=c++11 -c CPU.cpp

CPUProgram.o: CPUProgram.cpp
	g++ -std=c++11 -c CPUProgram.cpp

clean:
	rm *.o exe

