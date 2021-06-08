all: testa_lista

testa_lista: fila.o grafo_listaadj.o conectividade.o
	gcc -o conectividade_lista.exe fila.o grafo_listaadj.o conectividade.o

fila.o: fila.c fila.h
	gcc -c fila.c

grafo_listaadj.o: fila.c grafo_listaadj.c grafo_listaadj.h
	gcc -c grafo_listaadj.c

conectividade.o: fila.c conectividade.c grafo_listaadj.h
	gcc -c conectividade.c

clean:
	rm -f *.o *.exe