#ifndef __grafo__
#define __grafo__
#include "grafo.h"

typedef struct {
    int numero;
    int cor;
    Lista adjacentes;

} Vert;

typedef struct {
    Vert **vertices; // vertices do grafo
    int qtdVertices;
    int num;

} Graph;

Grafo criaGrafo(int num, int qtdCores, Lista vertices) {
    Graph *gr = (Graph *)malloc(sizeof(Graph));
    gr->num = num;
    gr->qtdVertices = tamanhoLista(vertices);
    gr->vertices = (Vert *)malloc(gr->qtdVertices * sizeof(Vert)); // alocando o vetor

    N nv = getFirst(vertices);

    for (int i = 0; i < gr->qtdVertices; i++) {
        gr->vertices[i] = getInfo(nv);
        nv = getNext(nv);
    }

    return gr;
}

Vertice criaVertice(int num, Lista adjacentes) {
    Vert *vertice = malloc(sizeof(Vert));
    vertice->numero = num;
    vertice->adjacentes = adjacentes;

    return vertice;
}

void printaGrafo(Grafo grafo) {

    Graph *gr = (Graph *)grafo;

    printf("Grafo %d\n", gr->num);

    for (int i = 0; i < gr->qtdVertices; i++) {

        printf("%d => ", gr->vertices[i]->numero);

        N *nv = getFirst(gr->vertices[i]->adjacentes);

        while (nv != NULL) {
            printf("%d ", getInfo(nv));
            nv = getNext(nv);
        }
        printf("\n");
    }
}

void destroiGrafo(Grafo grafo) {

    Graph *gr = (Graph *)grafo;

    for (int i = 0; i < gr->qtdVertices; i++) {
        destroiLista(gr->vertices[i]->adjacentes, NULL);
        free(gr->vertices[i]);
    }
    free(gr->vertices);
    free(gr);
}

#endif