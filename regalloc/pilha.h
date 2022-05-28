#ifndef __pilha__
#define __pilha__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
    - TAD relaciona à criação de uma pilha
    - Uma instância dessa pilha é ponteiro para uma Pilha

*/

typedef void *Pilha;
typedef void *Info; // informação que a pilha vai usar
typedef void visitaElem(Info);

/*
   cria uma pilha vazia
   sem requerimentos
   retorna uma pilha vazia
*/
Pilha criaPilha();

/*
   adiciona um elemento do tipo Info na pilha
   necessita de uma pilha já criada
   sem retorno
*/

void push(Pilha p, Info info);

/*
   remove o elemento do topo da lista
   necessita de uma pilha já criada com pelo menos 1 elemento
   sem retorno
*/
Info pop(Pilha p);

/*
   retorna o ponteiro info do elemento do topo da pilha
   necessita de uma pilha já criada com pelo menos 1 elemento
   retorna um ponteiro do tipo Info
*/
Info getInfoTopoPilha(Pilha p);

/*
   retorna o ponteiro info do elemento do após o elemento do topo da pilha
   necessita de uma pilha já criada com pelo menos 2 elementos
   retorna um ponteiro do tipo Info
*/
Info getInfoProxTopoPilha(Pilha p);

/*
   printa todos os elementos presentes na pilha, recebendo, além da Pilha, uma função de print
   necessita de uma pilha já criada com pelo menos 1 elemento
   sem retorno
*/
void printPilha(Pilha p, visitaElem fPrint);

/*
   retira todos os elementos da pilha
   necessita de uma pilha já criada com pelo menos 1 elemento
   sem retorno
*/
void destruirPilha(Pilha p, visitaElem fDesaloca);

/*
   verifica se uma pilha está vazia
   retorna 1 caso a pilha esteja vazia e 0 caso não esteja
*/
int isEmpty(Pilha p);

#endif
