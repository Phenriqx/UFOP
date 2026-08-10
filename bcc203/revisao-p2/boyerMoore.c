#include <stdio.h>

#include "boyerMoore.h"

/*
	Essa implementação seria como uma força bruta, onde a complexidade é O(n * m);
	O deslocamento da janela deslizante é sempre 1
*/

#define MAXCHAR 256

int boyerMoore(char *texto, char *padrao, int n, int m, int *mov) {
	int i, j, k, ult = 0;
	i = m;

	while (i <= n) {
		j = m;
		k = i;
		while (texto[k - 1] == padrao[j - 1] && j > 0) {
			j--;
			k--;
			if (j == 0) {
				printf("Casamento na posição %d\n", i - 1);
				ult = i - 1;
				break;
			}
		}
		*mov += 1;
		i++;
	}

	return ult;
}

int boyerMooreOcorrencia(char *texto, char *padrao, int n, int m, int *mov) {
	int i, j, k, ult = 0;
	i = m;
	int count;

	while (i <= n) {
		j = m;
		k = i;
		count = 0;
		while (j > 0) {
			if (texto[k - 1] == padrao[j - 1]) {
				j--;
				k--;
			}
			else {
				for (int l = j; padrao[l - 1] != texto[k - 1]; l--)
					count++;
				break;
			} 
		}
		if (j == 0) {
			printf("Casamento na posição %d\n", i - 1);
			ult = i - 1;
		}
		if (count != 0) {
			*mov += 1;
			i += count;
		}
		else {
			*mov += 1;
			i++;
		}
	}

	return ult;
}

int boyerMooreHorspool(char *texto, char *padrao, int n, int m, int *mov) {
	int i, j, k, ult = 0;
	int des[MAXCHAR + 1];
	
	for (j = 0; j <= MAXCHAR; j++)
		des[j] = m;

	for (j = 1; j < m; j++)
		des[padrao[j - 1]] = m - j;	
	
	i = m;
	while (i <= n) {
		*mov += 1;
		j = m;
		k = i;
		while (texto[k - 1] == padrao[j - 1] && j > 0) {
			j--;
			k--;
		}
		if (j == 0) {
			printf("Casamento na posição %d\n", i - 1);
			ult = i - 1;
		}
		i += des[texto[i - 1]];
	}

	return ult;	
}

int BHMS(char *texto, char *padrao, int n, int m, int *mov) {
	int i, j, k, ult = 0;
	int des[MAXCHAR + 1];
	
	for (j = 0; j <= MAXCHAR; j++)
		des[j] = m + 1;

	for (j = 1; j <= m; j++)
		des[padrao[j - 1]] = m - j + 1;	
	
	i = m;
	while (i <= n) {
		*mov += 1;
		j = m;
		k = i;
		while (texto[k - 1] == padrao[j - 1] && j > 0) {
			j--;
			k--;
		}
		if (j == 0) {
			printf("Casamento na posição %d\n", i - 1);
			ult = i - 1;
		}
		i += des[texto[i]];
	}

	return ult;	
}
