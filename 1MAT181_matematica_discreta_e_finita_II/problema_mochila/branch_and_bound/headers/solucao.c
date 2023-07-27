#include "solucao.h"
#include <stdlib.h>
#include <string.h>

No *copiarNo(No *n)
{
    No *novo;
    novo = (No *)malloc(sizeof(No));
    memcpy(novo, n, sizeof(No));
    return novo;
}

Variavel *criarVariavel(Item *item, No *n)
{
    Variavel *v;
    v = (Variavel *)malloc(sizeof(Variavel));
    v->item = (Item *)malloc(sizeof(Item));
    memcpy(v->item, item, sizeof(Item));
    v->n = copiarNo(n);
    return v;
}

void reiniciarVariavel(Variavel *v)
{
    if (v)
    {
        if (v->item)
            free((void *)v->item);
        if (v->n)
            free((void *)v->n);
        free((void *)v);
    }
}

Solucao *criarSolucao()
{
    Solucao *sol = (Solucao *)malloc(sizeof(Solucao));
    sol->variavel = NULL;
    sol->num_variavel = 0;
    sol->otima = 0;
    return sol;
}

void reiniciarSolucao(Solucao *sol)
{
    if (sol)
    {
        if (sol->variavel)
        {
            for (int i = 0; i < sol->num_variavel; i++)
                reiniciarVariavel(sol->variavel[i]);
            free((void *)sol->variavel);
        }
        free((void *)sol);
    }
}

void somarSolucao(Solucao *sol, Item *item, No *n)
{
    if (sol->variavel)
        sol->variavel = (Variavel **)realloc(sol->variavel, (sol->num_variavel + 1) * sizeof(Variavel *));
    else
        sol->variavel = (Variavel **)malloc(sizeof(Variavel *));
    sol->variavel[sol->num_variavel] = criarVariavel(item, n);
    sol->num_variavel++;
}

void escreverSolucao(Solucao *sol, FILE *file)
{
    fprintf(file, "Solucao otima: %d\n", sol->otima);
}