#ifndef ITEM_INCLUDED
#define ITEM_INCLUDED

#include <stdio.h>

#define MAX_LINHA 128

typedef struct {
    int peso, valor;
} Item;

Item *lerArquivo(char *, int *, int *);

double razaoItem(Item);

void escreverItem(Item *, FILE *);

void escreverItens(Item *, int, FILE *);

void quicksortRazao(Item *, int);

#endif