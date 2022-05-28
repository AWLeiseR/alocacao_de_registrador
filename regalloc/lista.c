#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    Info info;
    struct no *anterior;
    struct no *proximo;
} No;

typedef struct L {
    No *primeiro;
    No *ultimo;
    int tamanho;
    funcGetChave *fGetChave;
} list;

Lista create(funcGetChave f) {
    list *lista = (list *)malloc(sizeof(list));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
    lista->fGetChave = f;
    return lista;
}

N encontraNo(Lista L, char *chave) {
    list *lista = (list *)L;
    No *node = lista->primeiro;
    while (node != NULL) {
        if (strcmp(lista->fGetChave(node->info), chave) == 0)
            return node;

        node = node->proximo;
    }
}

void insert(Lista L, Info info) {
    list *lista = (list *)L;

    No *node = (No *)malloc(sizeof(No));
    node->info = info;
    if (lista->primeiro == NULL) {
        node->anterior = NULL;
        lista->primeiro = node;
    } else {
        lista->ultimo->proximo = node;
        node->anterior = lista->ultimo;
    }
    lista->tamanho++;
    node->proximo = NULL;
    lista->ultimo = node;
}

void insertAfter(Lista L, Info info, N n) {
    list *lista = (list *)L;
    No *no = (No *)n;
    No *aux = (No *)malloc(sizeof(No));
    aux->info = info;

    if (no->proximo == NULL) // se o nó recebido por parâmetro for o último
    {
        lista->ultimo = aux;
        aux->proximo = NULL;
    } else {
        aux->proximo = no->proximo;
        no->proximo->anterior = aux;
    }
    lista->tamanho++;
    no->proximo = aux;
    aux->anterior = no;
}

void insertBefore(Lista L, Info info, N n) {
    list *lista = (list *)L;
    No *no = (No *)n;
    No *aux = (No *)malloc(sizeof(No));
    aux->info = info;
    if (no->anterior == NULL) // se o nó recebido por parâmetro for o primeiro
    {
        lista->primeiro = aux;
        aux->anterior = NULL;
    } else {
        aux->anterior->proximo = no;
        no->anterior = aux->anterior;
    }
    lista->tamanho++;
    aux->proximo = no;
    no->anterior = aux;
}

Info deleteLista(Lista L, N n) {
    list *lista = (list *)L;
    No *node = (No *)n;
    Info inf = NULL;

    if (node != NULL) {
        inf = node->info;
        if (node->proximo == NULL && node->anterior == NULL) // se houver apenas 1 elemento na lista
        {
            lista->primeiro = NULL;
            lista->ultimo = NULL;
        } else if (node->anterior == NULL) // se for o primeiro
        {
            lista->primeiro = node->proximo;
            node->proximo->anterior = NULL;
        } else if (node->proximo == NULL) // se for o último
        {
            lista->ultimo = node->anterior;
            node->anterior->proximo = NULL;
        } else {
            node->anterior->proximo = node->proximo;
            node->proximo->anterior = node->anterior;
        }
        lista->tamanho--;
        free(node);
    }

    return inf;
}

int tamanhoLista(Lista L) {
    list *lista = (list *)L;
    return lista->tamanho;
}

N getFirst(Lista L) {
    list *lista = (list *)L;

    return lista->primeiro;
}

N getLast(Lista L) {
    list *lista = (list *)L;

    return lista->ultimo;
}

N getNext(N n) {
    No *no = (No *)n;

    return no->proximo;
}

N getPrevious(N n) {
    No *no = (No *)n;

    return no->anterior;
}

Info getInfo(N n) {
    No *node = (No *)n;

    return node->info;
}

void destroiLista(Lista L, void (*funcaoAuxiliar)(void *)) {
    list *lista = (list *)L;
    No *node = lista->primeiro;
    No *aux;

    while (node != NULL) {
        aux = node->proximo;
        if (funcaoAuxiliar != NULL)
            funcaoAuxiliar(node->info);

        free(node);
        node = aux;
    }
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    free(lista);
    lista = NULL;
}

void printaLista(Lista L, void (*printFunction)(void *, FILE *), FILE *arq) {
    list *lista = (list *)L;
    No *node = lista->primeiro;
    while (node != NULL) {
        printFunction(node->info, arq);
        node = node->proximo;
    }
}