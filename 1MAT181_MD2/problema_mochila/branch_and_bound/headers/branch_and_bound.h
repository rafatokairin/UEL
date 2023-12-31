#ifndef BRANCH_AND_BOUND_INCLUDED
#define BRANCH_AND_BOUND_INCLUDED
#include "item.h"
#include "solucao.h"

void escreverFila(void *dado);

void *alocarNoFila(void *);

int bound(Item *, int, int, No *);

/* utiliza uma fila que contém três nós e calcula o upper bound */
Solucao *branchAndBound(Item *, int, int);

void heuristica(char **, FILE *);

#endif
