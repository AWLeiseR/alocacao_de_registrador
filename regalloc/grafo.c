#ifndef __grafo__
#define __grafo__
#include "grafo.h"

typedef struct {
    int numero;
    int cor;
    Lista adjacentes; // lista de inteiros

} Vert;

typedef struct {
    Vert **vertices; // vertices do grafo
    int qtdVertices;
    int qtdVerticesOcupados;
    int num;
    int qtdCores;

} Graph;

Grafo criaGrafo(int num, Lista vertices) {
    Graph *gr = (Graph *)malloc(sizeof(Graph));
    gr->num = num;
    gr->qtdVertices = tamanhoLista(vertices);
    gr->qtdVerticesOcupados = gr->qtdVertices;
    gr->vertices = (Vert *)malloc(gr->qtdVertices * sizeof(Vert)); // alocando o vetor

    N nv = getFirst(vertices);

    for (int i = 0; i < gr->qtdVertices; i++) {
        gr->vertices[i] = getInfo(nv);
        nv = getNext(nv);
    }

    return gr;
}

void setQtdCoresGrafo(Grafo grafo, int qtdCores) {
    Graph *gr = (Graph *)grafo;
    gr->qtdCores = qtdCores;
}

int getNumGrafo(Grafo grafo) {
    Graph *gr = (Graph *)grafo;
    return gr->num;
}

int getQtdVerticesOcupados(Grafo grafo) {
    Graph *gr = (Graph *)grafo;
    return gr->qtdVerticesOcupados;
}

/*

a lista passada por parâmetro contém os numeros dos vertice que são adjacentes a este vertice
sejam eles registradores físicos ou virtuais
*/

Vertice criaVertice(int num, Lista adjacentes) {
    Vert *vertice = malloc(sizeof(Vert));
    vertice->numero = num;
    vertice->adjacentes = adjacentes;
    vertice->cor = -1;

    return vertice;
}

int getNumVertice(Vertice v) {
    Vert *vertice = (Vert *)v;
    return vertice->numero;
}

Lista getAdjacentesVertice(Vertice v) {
    Vert *vertice = (Vert *)v;
    return vertice->adjacentes;
}

int getCorVertice(Vertice v) {
    Vert *vertice = (Vert *)v;
    return vertice->cor;
}

Vert *getVertice(Graph *gr, int num) {

    for (int i = 0; i < gr->qtdVertices; i++) {
        Vert *v = gr->vertices[i];
        if (v != NULL && v->numero == num) {
            return v;
        }
    }

    return NULL;
}

int insereEColoreVertice(Grafo grafo, Vertice v) {
    Graph *gr = (Graph *)grafo;
    Vert *vert = (Vert *)v;

    /* iniciando vetor com as cores disponíveis */
    int *coresDisponiveis = malloc(sizeof(int) * gr->qtdCores);
    for (int i = 0; i < gr->qtdCores; i++) {
        coresDisponiveis[i] = 1;
    }

    /* verificando quais cores não estão disponíveis */
    N n = getFirst(vert->adjacentes);

    while (n != NULL) {

        int numVert = getInfo(n);

        if (numVert < gr->qtdCores) {      // registrador físico
            coresDisponiveis[numVert] = 0; // cor indisponível

        } else {
            Vert *i = getVertice(gr, numVert); // busca o vertice de tal número

            if (i != NULL && i->cor != -1) { // se ja possui uma cor atribuída
                coresDisponiveis[i->cor] = 0;
            }
        }
        n = getNext(n);
    }

    /* buscando a menor cor disponível */
    int cor = -1;
    for (int i = 0; i < gr->qtdCores; i++) {
        if (coresDisponiveis[i] == 1) {
            cor = i;
            break;
        }
    }

    free(coresDisponiveis);

    if (cor == -1) { /* não conseguiu colorir este vertice */
        return 0;
    }

    vert->cor = cor;
    gr->vertices[gr->qtdVerticesOcupados] = vert; // inserindo o vertice
    gr->qtdVerticesOcupados++;
    // printf("gr->qtdVerticesOcupados: %d     ", gr->qtdVerticesOcupados);
    return 1;
}

void removeAdjacencias(int numeroVertice, Graph *gr) {

    for (int i = 0; i < gr->qtdVertices; i++) {
        Vert *v = gr->vertices[i];

        if (v != NULL) {

            N n = getFirst(v->adjacentes);
            /* procura se há uma adjacência com o vertice com numero = numeroVertice*/
            while (n != NULL) {
                N aux = getNext(n);
                if (getInfo(n) == numeroVertice) {
                    deleteLista(v->adjacentes, n);
                }

                n = aux;
            }
        }
    }
}

Vertice removeVerticeGrauMenorQueK(Grafo grafo, int k) {

    Graph *gr = (Graph *)grafo;

    int menorGrau = -1;
    int menorNum = -1;
    Vert *v = NULL; // vertice escolhido para ser excluído
    int indexV = 0;

    for (int i = 0; i < gr->qtdVertices; i++) {

        Vert *j = gr->vertices[i];

        if (j != NULL) {

            int grau = tamanhoLista(j->adjacentes);
            int num = j->numero;

            if (menorGrau == -1 && grau < k) {
                menorGrau = grau;
                menorNum = num;
                v = j;
                indexV = i;

            } else {

                if (grau < k) {
                    if ((grau == menorGrau && num < menorNum) || grau < menorGrau) {
                        v = j;
                        indexV = i;
                        menorGrau = grau;
                        menorNum = num;
                    }
                }
            }
        }
    }

    if (v != NULL) {
        gr->qtdVerticesOcupados--;
        gr->vertices[indexV] = NULL;
        removeAdjacencias(menorNum, gr);
    }

    return v;
}

Vertice removeVerticeMaiorGrau(Grafo grafo) {

    Graph *gr = (Graph *)grafo;

    int maiorGrau = -1;
    int menorNum = -1;
    Vert *v = NULL; // vertice escolhido para ser excluído
    int indexV = 0;

    for (int i = 0; i < gr->qtdVertices; i++) {

        Vert *j = gr->vertices[i];

        if (j != NULL) {

            int grau = tamanhoLista(j->adjacentes);
            int num = j->numero;

            if (maiorGrau == -1) {
                maiorGrau = grau;
                menorNum = num;
                v = j;
                indexV = i;

            } else {

                if ((grau == maiorGrau && num < menorNum) || grau > maiorGrau) {
                    v = j;
                    indexV = i;
                    maiorGrau = grau;
                    menorNum = num;
                }
            }
        }
    }

    if (v != NULL) {
        gr->qtdVerticesOcupados--;
        gr->vertices[indexV] = NULL;
        removeAdjacencias(menorNum, gr);
    }

    return v;
}

int getNumeroVertice(Vertice v) {
    Vert *vert = (Vert *)v;
    return vert->numero;
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

void destroiGrafo(Grafo grafo, int desalocaAdjacentes) {

    Graph *gr = (Graph *)grafo;

    for (int i = 0; i < gr->qtdVertices; i++) {
        if (gr->vertices[i] != NULL) {
            desalocaVertice(gr->vertices[i], desalocaAdjacentes);
        }
    }
    free(gr->vertices);
    gr->vertices = NULL;
    free(gr);
    gr = NULL;
}

void setListaAdjacentesVertice(Vertice v, Lista adjacentes) {
    Vert *vert = (Vert *)v;
    vert->adjacentes = adjacentes;
}

void desalocaVertice(Vertice v, int desalocaAdjacentes) {

    Vert *vert = (Vert *)v;

    if (vert != NULL) {

        if (vert->adjacentes != NULL && desalocaAdjacentes == 1) {
            destroiLista(vert->adjacentes, NULL);
            vert->adjacentes = NULL;
        }
        free(vert);
        vert = NULL;
    }
}

#endif