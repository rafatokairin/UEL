#include <stdio.h>
#include <stdlib.h>

enum type {
    MIN, MAX
};

typedef struct {
    int pid;
    int prioridade;
    int tempoEspera;
} Processo;

void novoProcesso(Processo *proc, int* pid, int prioridade, int tempoEspera) 
{
    proc->pid = *pid;
    proc->prioridade = prioridade;
    proc->tempoEspera = tempoEspera;
    (*pid)++;
}

void substituir(Processo *a, Processo *b) 
{
    Processo x = *a;
    *a = *b;
    *b = x;
}

int heapVazio(int tam) 
{
    return (tam <= 0) ? 1 : 0;
}

void subirMax(Processo *heap, int i) 
{
    int pai = i / 2;
    if (pai >= 1) 
    {
        if (heap[i].prioridade > heap[pai].prioridade) 
        {
            substituir(&heap[i], &heap[pai]);
            subirMax(heap, pai);
        }
    }
}

void subirMin(Processo *heap, int i) 
{
    int pai = i / 2;
    if (pai >= 1) 
    {
        if (heap[i].tempoEspera < heap[pai].tempoEspera) 
        {
            substituir(&heap[i], &heap[pai]);
            subirMin(heap, pai);
        }
    }
}

void descerMax(Processo *heap, int i, int tam) 
{
    int maior = i;
    int esquerda = 2 * i;
    int direita = 2 * i + 1;

    if (esquerda <= tam && heap[esquerda].prioridade > heap[maior].prioridade)
        maior = esquerda;

    if (direita <= tam && heap[direita].prioridade > heap[maior].prioridade)
        maior = direita;

    if (maior != i) 
    {
        substituir(&heap[i], &heap[maior]);
        descerMax(heap, maior, tam);
    }
}

void descerMin(Processo *heap, int i, int tam) 
{
    int menor = i;
    int esquerda = 2 * i;
    int direita = 2 * i + 1;

    if (esquerda <= tam && heap[esquerda].tempoEspera < heap[menor].tempoEspera)
        menor = esquerda;

    if (direita <= tam && heap[direita].tempoEspera < heap[menor].tempoEspera)
        menor = direita;

    if (menor != i) 
    {
        substituir(&heap[i], &heap[menor]);
        descerMin(heap, menor, tam);
    }
}

void inserirProcesso(Processo **heap, Processo novo, int* tam, int tipo) 
{
    *heap = (Processo *)realloc(*heap, sizeof(Processo) * (*tam + 2));
    (*tam)++;
    (*heap)[*tam] = novo;
    if (tipo == MAX)
        subirMax(*heap, *tam);
    else    
        subirMin(*heap, *tam);
}

void imprimirProcesso(Processo *heapMax, Processo *heapMin, int tam, int tipo) 
{
    if (tipo == MAX) 
    {
        printf("\nPrioridade:\nHeapMax:\n");
        for(int i = 1; i <= tam; i++) 
            printf("%d ", heapMax[i].prioridade);
    }
    else 
    {
        printf("HeapMin:\n");
        for(int i = 1; i <= tam; i++) 
            printf("%d ", heapMin[i].tempoEspera);
    }
    printf("\n");
}

Processo removerProcessoTopo(Processo **heap, int *tam, int tipo) 
{
    Processo removido;
    if (heapVazio(*tam) != 0) 
    {
        removido = (*heap)[1];
        (*heap)[1] = (*heap)[*tam];
        (*tam)--;
        if (tipo == MAX)
            descerMax((*heap), 1, *tam);
        else    
            descerMin((*heap), 1, *tam);
    }
    return removido;
}

void construirHeapMax(Processo *heap, int tam) 
{
    int j = tam / 2;
    for (int i = j; i >= 1; i--)
        descerMax(heap, i, tam);
}

void construirHeapMin(Processo *heap, int tam) 
{
    int j = tam / 2;
    for (int i = j; i >= 1; i--)
        descerMin(heap, i, tam);
}

void gerarDotPrioridade(Processo *heap, const char* nome, int tam) 
{
    FILE* fdot = fopen(nome, "w");
    if (fdot == NULL) 
        return;
    fprintf(fdot, "digraph Heap {\n");
    for (int i = 1; i <= tam; i++) 
    {
        int esquerda = 2 * i;
        int direita = 2 * i + 1;
        if (esquerda <= tam) 
            fprintf(fdot, "%d -> %d\n", heap[i].prioridade, heap[esquerda].prioridade);
        if (direita <= tam) 
            fprintf(fdot, "%d -> %d\n", heap[i].prioridade, heap[direita].prioridade);
    }
    fprintf(fdot, "}\n");
    fclose(fdot);
}

void gerarDotTempoEspera(Processo *heap, const char* nome, int tam) 
{
    FILE* fdot = fopen(nome, "w");
    if (fdot == NULL) 
        return;
    fprintf(fdot, "digraph Heap {\n");
    for (int i = 1; i <= tam; i++) 
    {
        int esquerda = 2 * i;
        int direita = 2 * i + 1;
        if (esquerda <= tam) 
            fprintf(fdot, "%d -> %d\n", heap[i].tempoEspera, heap[esquerda].tempoEspera);

        if (direita <= tam) 
            fprintf(fdot, "%d -> %d\n", heap[i].tempoEspera, heap[direita].tempoEspera);
    }
    fprintf(fdot, "}\n");
    fclose(fdot);
}

int main() 
{
    int tamMax = 0, tamMin = 0, pid = 1;
    Processo proc;
    Processo *heapMax = (Processo *)malloc(sizeof(Processo));
    Processo *heapMin = (Processo *)malloc(sizeof(Processo));

    int opcao, prioridade, tempoEspera;
    do
    {
        printf("\n1. Inserir\n2. Remover\n3. Imprimir\n4. Sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Digite prioridade e tempo espera:\n");
            scanf("%d %d", &prioridade, &tempoEspera);
            novoProcesso(&proc, &pid, prioridade, tempoEspera);
            inserirProcesso(&heapMax, proc, &tamMax, MAX);
            inserirProcesso(&heapMin, proc, &tamMin, MIN);
            gerarDotPrioridade(heapMax, "prioridade.dot", tamMax);
            gerarDotTempoEspera(heapMin, "tempoEspera.dot", tamMin);
            break;
        case 2:
            Processo removidoMax = removerProcessoTopo(&heapMax, &tamMax, MAX);
            printf("\nProcesso removido do HeapMax:\nPrioridade: %d\n", removidoMax.prioridade);
            Processo removidoMin = removerProcessoTopo(&heapMin, &tamMin, MIN);
            printf("Processo removido do HeapMin:\nTempo de Espera: %d\n", removidoMin.tempoEspera);
            gerarDotPrioridade(heapMax, "prioridade.dot", tamMax);
            gerarDotTempoEspera(heapMin, "tempoEspera.dot", tamMin);
            break;
        case 3:
            imprimirProcesso(heapMax, heapMin, tamMax, MAX);
            imprimirProcesso(heapMax, heapMin, tamMax, MIN);
            break;
        case 4:
            printf("Finalizando...\n");
            free(heapMax);
            free(heapMin);
            break;
        default:
            break;
        }
    } while (opcao != 4);
    return 0;
}