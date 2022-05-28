#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    Info info; // void pointer para a informação que a pilha guardará
    struct No *prox;
} No;

typedef struct PILHA {
    No *topo;

} PILHA;

Pilha criaPilha() {
    PILHA *p = malloc(sizeof(PILHA));
    p->topo = NULL;

    return p;
}

void push(Pilha p, Info info) {
    PILHA *pilha = (PILHA *)p;
    No *node = malloc(sizeof(No));

    node->info = info;
    node->prox = pilha->topo;
    pilha->topo = node;
}

Info pop(Pilha p) {
    PILHA *pilha = (PILHA *)p;
    No *node = pilha->topo;
    No *aux = pilha->topo->prox;

    Info info = node->info;
    free(node);
    pilha->topo = aux;

    return info;
}

Info getInfoTopoPilha(Pilha p) {
    PILHA *pilha = (PILHA *)p;
    No *node = pilha->topo;

    if (node == NULL) {
        return NULL;
    }
    return node->info;
}

// retorna o info do proximo elemento do topo
Info getInfoProxTopoPilha(Pilha p) {
    PILHA *pilha = (PILHA *)p;
    No *node = pilha->topo->prox;

    if (node == NULL) {
        return NULL;
    }
    return node->info;
}

void printPilha(Pilha p, visitaElem fPrint) {

    PILHA *pilha = (PILHA *)p;
    No *node = pilha->topo;

    while (node != NULL) {
        fPrint(node->info);
        node = node->prox;
    }
    printf("\n");
}

void destruirPilha(Pilha p, visitaElem fDesaloca) {
    PILHA *pilha = (PILHA *)p;
    No *node = pilha->topo;
    No *aux;

    while (node != NULL) {
        aux = node->prox;
        if (fDesaloca != NULL)
            fDesaloca(node->info);
        free(node);
        node = aux;
    }
    free(pilha);
}

int isEmpty(Pilha p) {
    PILHA *pilha = (PILHA *)p;

    if (pilha->topo == NULL) {
        return 1;
    }
    return 0;
}