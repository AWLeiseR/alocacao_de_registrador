#include "grafo.h"
#include "lista.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int qtdCores; // k

/* variaveis que guardam os vertices e o grafo no estado em que eles
 ficam após o processo de build */
Lista vertices;

Grafo grafo;

void printaInt(void *info, FILE *file) {
    fprintf(file, "%d ", info);
}

Grafo copiaGrafo() {

    Lista verts = create(NULL);
    N no = getFirst(vertices);

    while (no != NULL) {
        Vertice v = getInfo(no);

        Lista adjs = getAdjacentesVertice(v);
        Lista adjsCopia = create(NULL);
        N n = getFirst(adjs);

        while (n != NULL) {
            insert(adjsCopia, getInfo(n));
            n = getNext(n);
        }

        Vertice vCopia = criaVertice(getNumeroVertice(v), adjsCopia);
        insert(verts, vCopia);

        no = getNext(no);
    }

    Grafo g = criaGrafo(getNumGrafo(grafo), verts);
    destroiLista(verts, NULL);
    return g;
}

Lista getListaAdjacentesVertice(int num) {

    N nv = getFirst(vertices);
    while (nv != NULL) {
        Vertice v = getInfo(nv);

        if (getNumeroVertice(v) == num) {
            return getAdjacentesVertice(v);
        }

        nv = getNext(nv);
    }
    return NULL;
}

/*
    Etapa de leitura do arquivo de teste bem como a criação do grafo com base nas inferências
*/
void build() {

    char linha[2500];
    char s[7];
    int numGrafo;

    fscanf(stdin, "%s %d %s\n", s, &numGrafo, s);

    fgets(linha, sizeof(linha), stdin);
    char *qtdCoresStr;
    qtdCoresStr = strtok(linha, "=");
    qtdCoresStr = strtok(NULL, "=");
    qtdCores = atoi(qtdCoresStr);

    vertices = create(NULL);

    while (fgets(linha, sizeof(linha), stdin) != NULL) {

        Lista adjacentes = create(NULL);
        int numReg;
        char *aux;
        int reg;

        numReg = atoi(strtok(linha, " "));

        aux = strtok(NULL, " ");

        while (aux != NULL) {
            aux = strtok(NULL, " ");
            if (aux != NULL) {
                reg = atoi(aux);
                insert(adjacentes, reg);
            }
        }

        Vertice v = criaVertice(numReg, adjacentes);
        insert(vertices, v);
    }

    grafo = criaGrafo(numGrafo, vertices);
    printf("Graph %d -> Physical Registers: %d\n", getNumGrafo(grafo), qtdCores);
    printf("%s\n", "----------------------------------------");
}

/*
    Etapa que consistem em remover os vértices do grafo que tiverem grau < k
*/
Pilha simplify(Grafo g) {

    Pilha p = criaPilha();

    while (getQtdVerticesOcupados(g) != 0) {

        Vertice v = removeVerticeGrauMenorQueK(g, qtdCores);
        int potSpill = 0;

        if (v == NULL) { // potencial spill
            v = removeVerticeMaiorGrau(g);
            potSpill = 1;

            if (v == NULL)
                break; /* grafo vazio*/
        }

        /* recuperando as adjacências */
        Lista adjs = getListaAdjacentesVertice(getNumeroVertice(v));
        destroiLista(getAdjacentesVertice(v), NULL);
        setListaAdjacentesVertice(v, adjs);
        push(p, v);

        if (potSpill)
            printf("Push: %d *\n", getNumeroVertice(v));
        else
            printf("Push: %d\n", getNumeroVertice(v));
    }

    return p;
}

/*
    Etapa de reinserção dos vértices no grafo e coloração
*/
int selectAssign(Grafo g, Pilha p) {

    int success = 1;
    while (!isEmpty(p)) {
        Vertice v = pop(p);

        if (success == 1) {

            if (insereEColoreVertice(g, v))
                printf("Pop: %d -> %d\n", getNumVertice(v), getCorVertice(v));

            else {
                printf("Pop: %d -> NO COLOR AVAILABLE\n", getNumVertice(v));
                desalocaVertice(v, 0);
                success = 0;
            }
        } else { // desaloca os vertices que permaneceram na pilha
            desalocaVertice(v, 0);
        }
    }

    destruirPilha(p, NULL);
    return success;
}

void main() {

    build();

    int tamResultados = qtdCores - 1;
    int c = 0;
    /* 1 -> Successful Allocation; 0 -> SPILL */
    int *resultados = calloc(tamResultados, sizeof(int));

    while (qtdCores > 1) {
        Grafo grafoCopia = copiaGrafo();
        setQtdCoresGrafo(grafoCopia, qtdCores);

        printf("----------------------------------------\n");
        printf("K = %d\n\n", qtdCores);

        Pilha p = simplify(grafoCopia);

        if (selectAssign(grafoCopia, p))
            resultados[c] = 1;

        destroiGrafo(grafoCopia, 0);
        qtdCores--;
        c++;
    }

    printf("----------------------------------------\n");
    printf("----------------------------------------");

    for (int i = 0; i < tamResultados; i++) {
        printf("\nGraph %d -> K = %*d: ", getNumGrafo(grafo), 2, tamResultados + 1 - i);
        if (resultados[i] == 1)
            printf("Successful Allocation");
        else
            printf("SPILL");
    }

    free(resultados);
    destroiLista(vertices, NULL);
    destroiGrafo(grafo, 1);
    return;
}