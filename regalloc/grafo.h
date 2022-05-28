#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef void *Grafo;

typedef void *Vertice;

Vertice criaVertice(int num, Lista adjacentes);

Grafo criaGrafo(int num, int qtdCores, Lista vertices);

void printaGrafo(Grafo grafo);

void destroiGrafo(Grafo grafo);