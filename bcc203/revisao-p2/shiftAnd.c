#include <stdio.h>

void ShiftAndAproximado(char* T, long n, char* P, long m, long k) {
    long Masc[256]; 
    long R[k + 1];
    long Rant, Rnovo, Ri;
    long i, j;

    for (i = 0; i < 256; i++) Masc[i] = 0;
    for (i = 0; i < m; i++) Masc[P[i]] |= (1 << (m - 1 - i));

    for (j = 0; j <= k; j++) R[j] = 0;

    Ri = 1 << (m - 1); 

    for (i = 0; i < n; i++) { 
        Rant = R[0]; 
        
        Rnovo = ((R[0] >> 1) | Ri) & Masc[T[i]]; 
        R[0] = Rnovo; 
        
        if ((R[0] & 1) != 0) {
            printf("Casamento exato na posicao %ld\n", i + 1);
        }

        for (j = 1; j <= k; j++) { 
            Rnovo = ((R[j] >> 1) & Masc[T[i]]) | (Rnovo >> 1) | Ri;
            
            Rant = R[j]; 
            R[j] = Rnovo; 
            
            if ((Rnovo & 1) != 0) {
                printf("Casamento aproximado (Retirada) com %ld erro(s) na posicao %ld\n", j, i + 1);
            }
        } 
    } 
}
