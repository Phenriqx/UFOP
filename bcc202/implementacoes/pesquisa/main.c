#include <stdio.h>

#include "binaria.h"

int main() {
    Dicionario *dicio = criarDicionario();

    dicioInsere(dicio);
    printDicio(dicio);

    int i = binarySearch(dicio, 0, 10, 10);
    printf("%d\n", i);

    freeDicionario(&dicio);
    return 0;
}