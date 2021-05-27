testa_lista: grafo_listaadj.o conectividade.o
	gcc -o conectividade_lista.exe grafo_listaadj.o conectividade.o

grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc -c grafo_listaadj.c

conectividade.o: conectividade.c grafo_listaadj.h
	gcc -c conectividade.c

clean:
	rm -f *.o *.exe