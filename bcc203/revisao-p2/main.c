#include "boyerMoore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char* texto = "ABRCCABABRACCAABRACCA";
	char* padrao = "BRACC";

	size_t n = strlen(texto);
	size_t m = strlen(padrao);
	int *mov, pos = 0;
	
	*mov = 0;

	// Boyer-Moore tradicional
	printf("Boyer-Moore Tradicional\n");
	pos = boyerMoore(texto, padrao, n, m, mov);	
	printf("Última posição encontrada: %d\n", pos);
	printf("Janela movida %d vezes\n", *mov);
	printf("=============\n\n");
	*mov = 0;

	// Boyer-Moore + Ocorrência
	printf("Boyer-Moore + Ocorrência\n");
	pos = boyerMooreOcorrencia(texto, padrao, n, m, mov);	
	printf("Última posição encontrada: %d\n", pos);
	printf("Janela movida %d vezes\n", *mov);
	printf("=============\n\n");
	*mov = 0;
	
	// Boyer-Moore + Casamento	

	// Boyer-Moore-Horspool
	printf("Boyer-Moore-Horspool\n");
	pos = boyerMooreHorspool(texto, padrao, n, m, mov);	
	printf("Última posição encontrada: %d\n", pos);
	printf("Janela movida %d vezes\n", *mov);
	printf("=============\n\n");
	*mov = 0;


	// Boyer-Moore-Horspool-Sunday
	printf("Boyer-Moore-Horspool-Sunday\n");
	pos = boyerMooreHorspool(texto, padrao, n, m, mov);	
	printf("Última posição encontrada: %d\n", pos);
	printf("Janela movida %d vezes\n", *mov);
	printf("=============\n\n");
	*mov = 0;

	return 0;
}
