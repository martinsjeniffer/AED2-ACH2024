all: testa_lista

testa_lista: filaBL.o grafo_listaadj.o conectividade.o
	gcc -o conectividade_lista.exe filaBL.o grafo_listaadj.o conectividade.o

filaBL.o: filaBL.c filaBL.h
	gcc -c filaBL.c

grafo_listaadj.o: filaBL.c grafo_listaadj.c grafo_listaadj.h
	gcc -c grafo_listaadj.c

conectividade.o: filaBL.c conectividade.c grafo_listaadj.h
	gcc -c conectividade.c

clean:
	rm -f *.o *.exe