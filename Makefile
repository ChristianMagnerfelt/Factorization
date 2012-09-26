all: main.o
	g++ -o Main main.o -lgmpxx -lgmp
main.o: main.cpp
	g++ -c -Wall main.cpp
clean:
	rm -f *.o Main
