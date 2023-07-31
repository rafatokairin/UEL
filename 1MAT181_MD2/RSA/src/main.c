#include "../headers/criptografa.h"
#include "../headers/primo.h"
#include "../headers/phi_n.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

int main()
{
    int p, q;
    uint64_t n, phi_n, e, d, senha_cript[MAX_SENHA];
    srand(time(NULL));
    p = geraPrimo(10000, 50000);
    q = geraPrimo(10000, 50000);
    while (p == q)
        geraPrimo(10000, 50000);
    
    // calcula n e phi_n
    n = p * q;
    phi_n = (p - 1) * (q - 1);

    // escolhe um "e" coprimo de phi_n aleatório (3 <= e <= phi_n - 1)
    e = coprimo(phi_n);

    // calcula inverso modular de "e": (e * d) mod(phi_n) = 1
    d = inversoMod(e, phi_n);

    // infos
    char senha[MAX_SENHA] = "RSA1977!";
    printf("Senha original: %s\n", senha);
    printf("p: %d\n", p);
    printf("q: %d\n", q);
    printf("Totiente(n): %lu\n", phi_n);
    printf("Chave pública: [n: %lu, e: %lu]\n", n, e);
    printf("Chave privada: [d: %lu]\n", d);
    printf("\nSenha criptografada: ");
    criptografa(senha, senha_cript, e, n);
    printf("\nSenha descriptografada: ");
    descriptografa(senha_cript, d, n);
    printf("\n");
    return 0;
}