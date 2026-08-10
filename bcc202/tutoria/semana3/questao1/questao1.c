#include <stdio.h>

int calculaSomaRec(int n);

int main() {
    int n;
    printf("Insira um número inteiro: ");
    scanf("%d", &n);

    int res = calculaSomaRec(n);
    printf("A soma dos números de 1 até %d é: %d\n", n, res);

    return 0;
}

int calculaSomaRec(int n) {
    if (n == 1)
        return 1;

    return n + calculaSomaRec(n - 1);
}

/*
Equação de recorrência:

Analisando os dois casos da função:
    Caso base:
        if (n == 1) return 1;
        custo constante, T(1) = c1

    Caso recursivo:
        return n + calculaSomaRec(n - 1);
        o custo é a chamada recursiva (T(n - 1)) e o custo de operações constantes (add e return) -> T(n - 1) + c2;

    Expandindo:

        T(n) = T(n - 1) + c
        T(n - 1) = T((n - 1) - 1) + c => T(n - 1) = T(n - 2) + c
        Substituindo esse valor na equação original:
            T(n) = (T(n - 2) + c) + c
            T(n) = T(n - 2) + 2c

        Se continuarmos a expandir o resultado é semelhante:
            T(n) = T(n - 3) + 3c...

    Então o padrão é: T(n) = T(n - k) + kc
    A condição de parada é T(1), então n - k = 1 => k = n - 1;

    T(n) = T(n - (n - 1)) + (n - 1)c
    T(n) = T(1) + (n - 1)c

    Como T(1) = c1 ==> T(n) = c1 + cn - c ou T(n) = cn + (c1 - c)

Complexidade temporal é O(n) pois podemos desconsiderar as contantes, ficando somente com n.
*/