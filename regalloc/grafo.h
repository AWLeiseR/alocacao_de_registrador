#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef void *Grafo;

typedef void *Vertice;

Grafo criaGrafo(int num, Lista vertices);

void setQtdCoresGrafo(Grafo grafo, int qtdCores);

int getNumGrafo(Grafo grafo);

int getQtdVerticesOcupados(Grafo grafo);

Vertice criaVertice(int num, Lista adjacentes);

int insereEColoreVertice(Grafo grafo, Vertice v);

int getCorVertice(Vertice v);

Lista getAdjacentesVertice(Vertice v);

int getNumVertice(Vertice v);

Vertice removeVerticeGrauMenorQueK(Grafo grafo, int k);

Vertice removeVerticeMaiorGrau(Grafo grafo);

int getNumeroVertice(Vertice v);

void printaGrafo(Grafo grafo);

void setListaAdjacentesVertice(Vertice v, Lista adjacentes);

void destroiGrafo(Grafo grafo, int desalocaAdjacentes);

void desalocaVertice(Vertice v, int desalocaAdjacentes);