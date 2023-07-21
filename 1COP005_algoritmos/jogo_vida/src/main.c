#include "../headers/vida.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    int **matriz, **geracao;
    leitura(argc, argv, &matriz, &geracao);
    // imprime as geracoes (VIVOS = "#"; MORTOS = ".")
    imprimir(matriz, geracao, atoi(argv[2]));
    reiniciar(matriz, geracao);
    free(matriz);
    free(geracao);
    return 0;
}