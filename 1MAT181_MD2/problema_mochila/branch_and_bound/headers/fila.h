#ifndef FILA_INCLUDED
#define FILA_INCLUDED

struct noFila {
    void *dado;
    struct noFila *prox;
};

typedef struct {
    struct noFila *ini, *fim, *temp, *temp2;
    int tam;
    void *(*func_alocar)(void *);
} Fila;

Fila *criarFila(void *(*func_alocar)(void *));

void reiniciarFila(Fila *);

void pushFila(Fila *, void *);

void popFila(Fila *);

/* Retorna o elemento ini */
void *proxFila(Fila *);

/* Retorna 1 se Fila estiver vazia, 0 caso contrário */
int verificaFila(Fila *);

#endif