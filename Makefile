FLAGS = -Wall -g -o

all: Analyseur

clean:
	rm -rf *.o Analyseur

Trame.o : Trame.c Trame.h 
	gcc -c $(FLAGS) $@ $<

Analyse.o : Analyse.c Analyse.h
	gcc -c $(FLAGS) $@ $<

Analyseur.o : Analyseur.c Trame.h Analyse.h
	gcc -c $(FLAGS) $@ $<

Analyseur : Analyseur.o Trame.o Analyse.o
	gcc $(FLAGS) $@ $^ -lm