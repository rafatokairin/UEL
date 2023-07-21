#include "vida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int vizinhos(int **M, int i, int j)
{
    int conta = 0;
    if (i - 1 >= 0 && j - 1 >= 0)
        if (M[i - 1][j - 1] >= 1)
            conta++;
    if (i - 1 >= 0)
        if (M[i - 1][j] >= 1)
            conta++;
    if (i - 1 >= 0 && j + 1 < TAM)
        if (M[i - 1][j + 1] >= 1)
            conta++;
    if (j - 1 >= 0)
        if (M[i][j - 1] >= 1)
            conta++;
    if (j + 1 < TAM)
        if (M[i][j + 1] >= 1)
            conta++;
    if (i + 1 < TAM && j - 1 >= 0)
        if (M[i + 1][j - 1] >= 1)
            conta++;
    if (i + 1 < TAM)
        if (M[i + 1][j] >= 1) 
            conta++;
    if (i + 1 < TAM && j + 1 < TAM)
        if (M[i + 1][j + 1] >= 1)
            conta++;
    return conta;
}

void leitura(int argc, char **argv, int ***matriz, int ***geracao)
{
    if (argc != 3)
    {
        printf("Quantidade de argumentos invalida!\n");
        exit(1);
    }

    *matriz = (int **)calloc(TAM, sizeof(int *));
    *geracao = (int **)calloc(TAM, sizeof(int *));
    for (int i = 0; i < TAM; i++)
    {
        (*matriz)[i] = (int *)calloc(TAM, sizeof(int));
        (*geracao)[i] = (int *)calloc(TAM, sizeof(int));
    }

    char pasta[] = "./compile/";
    char *path = (char *)malloc(strlen(pasta) + strlen(argv[1]) + 1);
    strcpy(path, pasta);

    FILE *quadro = fopen(strcat(path, argv[1]), "r");
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (!feof(quadro))
                fscanf(quadro, "%d", &(*matriz)[i][j]);
    fclose(quadro);
    free(path);
}

void imprimir(int **matriz, int **geracao, int num_geracao)
{
    for (int qtde_geracao = 0; qtde_geracao < num_geracao; ++qtde_geracao)
    {
        for (int i = 0; i < TAM; ++i)
        {
            for (int j = 0; j < TAM; ++j)
            {
                if (matriz[i][j] == 1)
                    printf("# ");
                else
                    printf(". ");
                // matriz com a respectiva quantidade de vizinhos de cada célula
                geracao[i][j] = vizinhos(matriz, i, j);
            }
            printf("\n");
        }
        printf("\n\n");
        // analisa se a celula vai viver ou morrer de acordo com a quantidade de seus vizinhos
        for (int i = 0; i < TAM; ++i)
        {
            for (int j = 0; j < TAM; ++j)
            {
                if (matriz[i][j] >= 1)
                {
                    if (geracao[i][j] <= 1 || geracao[i][j] >= 4)
                        matriz[i][j] = 0;
                }
                else if (geracao[i][j] == 3)
                    matriz[i][j] = 1;
            }
        }
        sleep(1);
    }
}

void reiniciar(int **matriz, int **geracao)
{
    for (int i = 0; i < TAM; i++)
    {
        free(matriz[i]);
        free(geracao[i]);
    }
}