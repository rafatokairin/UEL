#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

Fila *criarFila(void *(*func_alocar)(void *))
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    f->tam = 0;
    f->func_alocar = func_alocar;
    return f;
}

void reiniciarFila(Fila *f)
{
    if (f)
    {
        for (int i = 0; i < f->tam; i++)
            popFila(f);
        free((void *)f);
    }
}

void pushFila(Fila *f, void *dado)
{
    if (f->fim == NULL)
    {
        f->fim = (struct noFila *)malloc(sizeof(struct noFila));
        f->fim->prox = NULL;
        f->fim->dado = f->func_alocar(dado);
        f->ini = f->fim;
    }
    else
    {
        f->temp = (struct noFila *)malloc(sizeof(struct noFila));
        f->fim->prox = f->temp;
        f->temp->dado = f->func_alocar(dado);
        f->temp->prox = NULL;
        f->fim = f->temp;
    }
    f->tam++;
}

void popFila(Fila *f)
{
    f->temp2 = f->ini;
    if (f->temp2 == NULL)
        return;
    else
    {
        if (f->temp2->prox != NULL)
        {
            f->temp2 = f->temp2->prox;
            free((void *)f->ini->dado);
            free((void *)f->ini);
            f->ini = f->temp2;
        }
        else
        {
            free((void *)f->ini->dado);
            free((void *)f->ini);
            f->ini = NULL;
            f->fim = NULL;
        }
        f->tam--;
    }
}

void *proxFila(Fila *f)
{
    if (f->ini != NULL && f->fim != NULL)
        return f->ini->dado;
    else
        return NULL;
}

int verificaFila(Fila *f)
{
    return f->ini == NULL && f->fim == NULL;
}