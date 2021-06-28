all: EP1

EP1: fila.o grafoListaAdj.o conectividade.o
	gcc -o conectividade.exe fila.o grafoListaAdj.o conectividade.o

fila.o: fila.c fila.h
	gcc -c fila.c

grafoListaAdj.o: fila.c grafoListaAdj.c grafoListaAdj.h
	gcc -c grafoListaAdj.c

conectividade.o: fila.c conectividade.c grafoListaAdj.h
	gcc -c conectividade.c

clean:
	rm -f *.o *.exe