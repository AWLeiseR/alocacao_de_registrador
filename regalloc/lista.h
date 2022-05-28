#ifndef __lista__
#define __lista__

#include "stdio.h"

/* 
    TAD relacionado a criação de uma lista duplamente encadeada.
    Uma instância desse TAD é uma lista duplamente encadeada.


*/
//representa um nó da lista
typedef void *N;
//representa um ponteiro para a lista
typedef void *Lista;
//representa as informações desse nó, que aponta para um outro TAD específico de uma das figuras:
//círculos, retangulos, textos, quadras, semaforos, radio-bases, semaforos ou hidrantes
typedef void *Info;
//função que retorna a chave de ordenação do dado armazenado
typedef char *funcGetChave(Info);

/*
   cria uma lista vazia
   requer uma função que retorna a chave de ordenação do tipo dado a ser armazenado na lista caso seja necessário, do contrário passa NULL como argumento
   retorna uma lista vazia
*/
Lista create(funcGetChave f);

/*
  insere um elemento na lista
  necessita de uma já lista iniciada
  recebe como parâmetro o ponteiro para a lista já iniciada e um ponteiro do tipo Info, que aponta para um outro TAD específico da figura
  nao retorna nada
*/
void insert(Lista L, Info info);

/*
  insere um elemento após um outro elemento da lista
  necessita que uma lista já criada, com pelo menos 1 elemento já inserido
  recebe como parâmetro:
  - o ponteiro para a lista já iniciada 
  - o ponteiro do tipo Info, que aponta para um outro TAD específico da figura
  - o ponteiro do tipo N, que aponta para um nó de um elemento da lista
  nao retorna nada
*/
void insertAfter(Lista L, Info info, N n);

/*
  insere um elemento antes de um outro elemento da lista
  necessita que uma lista já criada, com pelo menos 1 elemento já inserido
  recebe como parâmetro:
  - o ponteiro para a lista já iniciada 
  - o ponteiro do tipo Info, que aponta para um outro TAD específico da figura
  - o ponteiro do tipo N, que aponta para um nó de um elemento da lista
  nao retorna nada
*/
void insertBefore(Lista L, Info info, N n);

/*
  deleta um elemento lista
  necessita que uma lista já criada, com pelo menos 1 elemento já inserido
  recebe como parâmetro:
  - o ponteiro para a lista já iniciada 
  - o no do elemento a ser excluído
  - retorna o ponteiro para a informação guardada no nó
*/
Info deleteLista(Lista L, N n);

/*
  necessita que uma lista já criada, com pelo menos 1 elemento já inserido
   recebe como parâmetro:
  - o ponteiro para uma lista já iniciada
  retorna a quantidade de elementos da lista
*/
int tamanhoLista(Lista L);

/*
  encontra e retorna o primeiro elemento de uma lista
  necessita que uma lista já criada, com pelo menos 1 elemento já inserido
   recebe como parâmetro:
  - o ponteiro para uma lista já iniciada
  retorna o primeiro elemento de uma lista
*/
N getFirst(Lista L);

/*
  encontra e retorna o ultimo elemento de uma lista
  necessita que uma lista já criada, com pelo menos 1 elemento já inserido
   recebe como parâmetro:
  - o ponteiro para uma lista já iniciada
  retorna o ultimo elemento de uma lista
*/
N getLast(Lista L);

/*
  encontra e retorna o proximo de um elemento de uma lista
  necessita que uma lista já criada, com pelo menos 1 elemento já inserido
   recebe como parâmetro:
  - o ponteiro para nó
  retorna o proximo de um elemento de uma lista
*/
N getNext(N n);

/*
  encontra e retorna o anterior de um elemento de uma lista
  necessita que uma lista já criada, com pelo menos 1 elemento já inserido
   recebe como parâmetro:
  - o ponteiro para nó
  retorna o anterior de um elemento de uma lista
*/
N getPrevious(N n);

/*
  retorna o ponteiro Info de um elemento de uma lista
  necessita que uma lista já criada, com pelo menos 1 elemento já inserido
   recebe como parâmetro:
  - o ponteiro para nó
  retorna o ponteiro Info de um elemento de uma lista
*/
Info getInfo(N n);

/*
  desaloca todos os elementos de uma lista
  necessita que uma lista já criada
  recebe como parâmetro:
  - o ponteiro para uma lista já iniciada
  - pode receber uma função auxiliar para desalocar os registros Info armazenados na lista, 
    caso não seja o objetivo desalocar esses elementos, NULL deve ser passado como argumento
  nao retorna nada
*/
void destroiLista(Lista L, void (*funcaoAuxiliar)(void *));

void printaLista(Lista L, void (*printFunction)(void *, FILE *), FILE *arq);

/*
  encontra o nó na lista que contém a chave de ordenação chave
  necessita que uma lista já criada, com pelo menos 1 elemento já inserido
  recebe como parâmetro:
  - o ponteiro para uma lista já iniciada
  - um char* contendo a chave do nó
  retorna o nó caso seja encontrado, do contrário retorna NULL
*/
N encontraNo(Lista L, char *chave);

#endif
