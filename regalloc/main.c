#include "grafo.h"
#include "lista.h"
#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printaInt(void *info, FILE *file) {
    fprintf(file, "%d ", info);
}

/*
    Etapa de leitura do arquivo de teste bem como a criação do grafo com base nas inferências
*/
Grafo build() {

    char linha[1000];
    char s[7];
    int numGrafo;

    fscanf(stdin, "%s %d %s\n", s, &numGrafo, s);

    // printf("%s %d\n", s, numGrafo);

    fgets(linha, sizeof(linha), stdin);
    // printf("%s", linha);
    char *qtdCoresStr;
    qtdCoresStr = strtok(linha, "=");
    qtdCoresStr = strtok(NULL, "=");
    int qtdCores = atoi(qtdCoresStr);
    // printf("%d", qtdCores);

    Lista vertices = create(NULL);

    while (fgets(linha, sizeof(linha), stdin) != NULL) {

        Lista adjacentes = create(NULL);

        int numReg;
        char *aux;

        // printf("%s", linha);

        numReg = atoi(strtok(linha, " "));
        // printf("%d ", numReg);

        aux = strtok(NULL, " ");
        // printf("%s ", aux);

        int reg;

        while (aux != NULL) {
            aux = strtok(NULL, " ");
            if (aux != NULL) {
                reg = atoi(aux);
                insert(adjacentes, reg);
                // printf("%s %d\n", aux, reg);
                // printf("%d ", atoi(aux));
            }
        }

        Vertice v = criaVertice(numReg, adjacentes);
        insert(vertices, v);
        // printaLista(adjacentes, printaInt, stdout);
        // printf("\n");
    }

    Grafo g = criaGrafo(numGrafo, qtdCores, vertices);
    printaGrafo(g);
    destroiLista(vertices, NULL);

    return g;
}

void simplify(Grafo g) {

    Pilha p = criaPilha();
}

void main() {

    Grafo g = build();

    destroiGrafo(g);

    return;
}