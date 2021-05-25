all: grafo.exe
 
grafo.exe: testa_grafo.o 
	gcc -o grafo.exe testa_grafo.o

testa_grafo.o: testa_grafo.c grafo.c
	gcc -c testa_grafo.c grafo.c
 
grafo.o: grafo.c grafo.h
	gcc -c grafo.c
 
clean:
	rm -rf *.o *.exe