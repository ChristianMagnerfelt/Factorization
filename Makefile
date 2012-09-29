all: factoring.o
	g++ -o Factoring factoring.o -lgmpxx -lgmp
main.o: factoring.cpp
	g++ -c -Wall factoring.cpp
clean:
	rm -f *.o Main
