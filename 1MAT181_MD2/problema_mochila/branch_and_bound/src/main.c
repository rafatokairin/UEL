#include "../headers/branch_and_bound.h"
#include "../headers/item.h"
#include "../headers/solucao.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        exit(EXIT_FAILURE);
    FILE *file = stdout;
    heuristica(argv, file);
    if (file != stdout)
        fclose(file);
    exit(EXIT_SUCCESS);
}
