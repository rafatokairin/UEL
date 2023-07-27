#include "item.h"
#include <errno.h>
#include <stdlib.h>

int numLinhas(FILE *file)
{
    int lin = 0;
    char c;
    fseek(file, 0, SEEK_SET);
    while (!feof(file))
    {
        c = fgetc(file);
        if(c == '\n')
            lin++;
    }
    fseek(file, 0, SEEK_SET);
    return lin;
}

Item *lerArquivo(char *file_name, int *num_item, int *max_peso)
{
    FILE *file = NULL;
    char lin[MAX_LINHA];
    int i = 0, peso = 0, valor = 0;
    Item *item = NULL;
    *num_item = 0;
    *max_peso = 0;

    if (!(file = fopen(file_name, "r")))
        return NULL;

    *num_item = numLinhas(file) - 1;
    fgets(lin, MAX_LINHA, file);
    sscanf(lin, "%d\n", max_peso);

    item = (Item *)malloc(*num_item * sizeof(Item));
    while (fgets(lin, MAX_LINHA, file)) {
        sscanf(lin, "%d %d\n", &peso, &valor);
        item[i].peso = peso;
        item[i].valor = valor;
        i++;
    }
    fclose(file);
    return item;
}

double razaoItem(Item item)
{
    return (double)item.valor / item.peso;
}

void escreverItem(Item *item, FILE *file)
{
    fprintf(file, "item : peso:%d valor:%d razao:%lf", item->peso, item->valor, razaoItem(*item));
}

void escreverItens(Item *item, int num_item, FILE *file)
{
    for (int i = 0; i < num_item; i++)
    {
        escreverItem(&item[i], file);
        fprintf(file, "\n");
    }
}

void quicksortRazao(Item *item, int num_item)
{
    int i, j, temp_valor, temp_peso;
    double pivo;

    if (num_item < 2)
        return;

    pivo = razaoItem(item[num_item / 2]);

    for (i = 0, j = num_item - 1; i <= j; i++, j--)
    {
        while (razaoItem(item[i]) > pivo)
            i++;
        while (razaoItem(item[j]) < pivo)
            j--;
        if (i >= j)
            break;
        temp_valor = item[i].valor;
        temp_peso = item[i].peso;
        item[i].valor = item[j].valor;
        item[i].peso = item[j].peso;
        item[j].valor = temp_valor;
        item[j].peso = temp_peso;
    }
    quicksortRazao(item, i);
    quicksortRazao(item + i, num_item - i);
}