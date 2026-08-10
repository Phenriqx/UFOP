#include "lista.h"

int main() {
    Lista* l = criaLista();

    listaPush(l, "Gustavo", 30);
    listaPush(l, "Jorge", 60);
    listaPush(l, "Pedro", 19);
    listaPush(l, "Regina", 63);
    listaPush(l, "Lara", 20);

    printLista(l);

    return 0;
}
