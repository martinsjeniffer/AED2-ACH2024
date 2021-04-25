testa_lista: grafo_listaadj.o testa_grafo.o
	gcc -o testa_grafo_lista.exe grafo_listaadj.o testa_grafo.o

grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc -c grafo_listaadj.c

testa_grafo.o: testa_grafo.c grafo_listaadj.h
	gcc -c testa_grafo.c

clean:
	rm -f *.o *.exe