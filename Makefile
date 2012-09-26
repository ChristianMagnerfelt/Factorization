all: main.o
	g++ -o Main main.o
main.o: 
	g++ -c -Wall main.cpp -lgmp -lgmpxx
clean:
	rm -f *.o Main
