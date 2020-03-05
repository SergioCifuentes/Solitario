# compila los archivos e=necesarios
all: lista
lista: main.o
	g++ main.o -o lista
	./lista
main.o: 
   g++ -c main.cpp
	
clean:	
	rm -rf *o main