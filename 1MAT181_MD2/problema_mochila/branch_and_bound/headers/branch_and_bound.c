#include "branch_and_bound.h"
#include "fila.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void *alocarNoFila(void *dado)
{
    No *n = (No *)malloc(sizeof(No));
    memcpy(n, (No *)dado, sizeof(No));
    return (void *)n;
}

int bound(Item *item, int num_item, int max_peso, No *u)
{
    if (u->peso >= max_peso)
        return 0;
    int lucro_bound = u->lucro;
    int i = u->altura + 1;
    int peso = u->peso;

    /**
     * Enquanto não alcançar o número máximo de Nós e não alcançar o peso máximo:
     *     - Aumentar o peso total com o peso do Item atual
     *     - Aumentar o lucro total com o valor do Item atual
     */
    while (i < num_item && peso + item[i].peso <= max_peso)
    {
        peso = peso + item[i].peso;
        lucro_bound = lucro_bound + item[i].valor;
        i++;
    }

    /**
     * Caso não alcance o número máximo de Nós,
     * utilizar método fracionário para calcular o melhor lucro,
     * aumentando assim as chances de preencher completamente a mochila.
     */
    if (i < num_item)
        lucro_bound = lucro_bound + (max_peso - peso) * razaoItem(item[i]);
    return lucro_bound;
}

Solucao *branchAndBound(Item *item, int num_item, int max_peso)
{
    No u, v;
    int max_lucro, encontra_max_lucro;
    u.altura = -1;
    u.lucro = 0;
    u.peso = 0;
    max_lucro = 0;
    Solucao *sol = criarSolucao();
    Fila *f = criarFila(alocarNoFila);
    pushFila(f, (void *)&u);

    quicksortRazao(item, num_item);
    /* Existe ramo para explorar? */
    while (!verificaFila(f))
    {
        encontra_max_lucro = 0;
        u = *(No *)proxFila(f);
        /* Deletar Nó que obtivemos */
        popFila(f);
        v.altura = 0;
        v.altura = u.altura + 1;
        v.peso = u.peso + item[v.altura].peso;
        v.lucro = u.lucro + item[v.altura].valor;
        /**
         * Se o peso for menor que o peso máximo e o lucro for maior que o
         * melhor lucro, atualizamos o melhor lucro conhecido.
         */
        if (v.peso <= max_peso && v.lucro > max_lucro)
        {
            max_lucro = v.lucro;
            encontra_max_lucro = 1;
        }
        /* Podar arvore */
        v.bound = bound(item, num_item, max_peso, &v);
        if (v.bound > max_lucro)
        {
            pushFila(f, (void *)&v);
            if (encontra_max_lucro)
                somarSolucao(sol, &item[v.altura], &v);
        }
        v.peso = u.peso;
        v.lucro = u.lucro;
        v.bound = bound(item, num_item, max_peso, &v);
        if (v.bound > max_lucro)
            pushFila(f, (void *)&v);
    }
    reiniciarFila(f);
    sol->otima = max_lucro;
    return sol;
}

void heuristica(char *file_name, char **argv, FILE *file)
{
    Item *item;
    Solucao *sol;
    int num_item, max_peso;
    clock_t begin_clock, end_clock;
    if (!(item = lerArquivo(argv[1], &num_item, &max_peso)))
    {
        fprintf(stderr, "ERRO ao carregar dados arquivo!\n");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Capacidade: %d\n", max_peso);
    begin_clock = clock();
    sol = branchAndBound(item, num_item, max_peso);
    end_clock = clock();
    escreverSolucao(sol, file);
    fprintf(file, "Tempo de execucao: %fs\n", (double)(end_clock - begin_clock) / CLOCKS_PER_SEC);
    reiniciarSolucao(sol);
    free((void *)item);
}