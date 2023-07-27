#ifndef SOLUCAO_INCLUDED
#define SOLUCAO_INCLUDED
#include "item.h"
#include <stdio.h>

typedef struct {
    int altura, lucro, bound, peso;
} No;

No *copiarNo(No *);

typedef struct {
    Item *item;
    No *n;
} Variavel;

Variavel *criarVariavel(Item *, No *);

void reiniciarVariavel(Variavel *);

typedef struct {
    Variavel **variavel;
    int num_variavel, otima;
} Solucao;

Solucao *criarSolucao();

void reiniciarSolucao(Solucao *);

void somarSolucao(Solucao *, Item *, No *);

void escreverSolucao(Solucao *, FILE *);

#endif