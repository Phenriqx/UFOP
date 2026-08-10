#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    MapaCidades *mapa= criaMapa(n, m);

    int result = chamaCaminho(mapa);
    if (result)
        printf("SIM\n");
    else 
        printf("NAO\n");
    
    liberaMapa(&mapa);
    return 0;
}