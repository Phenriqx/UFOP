#include <stdio.h>

#include "hash.h"


int main() {
    Hash hash;
    Chave chave;
    int n, m, p, s, peso_val, ultimo_res;

    if (scanf("%d", &n) != 1)
        return 0;

    while (n-- > 0) {
        if (scanf("%d %d", &m, &p) != 2) break;

        inicia(&hash, m, p);

        for (int i = 0; i < p; i++) {
            scanf("%d", &peso_val);
            hash.pesos[i] = peso_val;
        }

        if (scanf("%d", &s) != 1) {
            libera(&hash);
            break;
        }

        for (int i = 0; i < s; i++) {
            scanf("%s", chave);
            ultimo_res = insere(&hash, chave);
        }

        printf("%d\n", ultimo_res);

        libera(&hash);
    }

    return 0;
}