#include <stdio.h>
#include <string.h>

#define MAX 256

int reconheceL1(char l1[MAX], int l, int r);
int reconheceL2(char l2[MAX], int i, int contA, int contB);

int main() {
	char str[MAX];
	printf("Insira a palavra: ");
	scanf("%s", str);

	int val1 = reconheceL1(str, 0, strlen(str) - 1);
	if (val1)
		printf("Pertence a linguagem L1\n");
	else
		printf("Não pertence a linguagem L1\n");

	int val2 = reconheceL2(str, 0, 0, 0);
	if (val2)
		printf("Pertence a linguagem L2\n");
	else
		printf("Não pertence a linguagem L2\n");

	return 0;
}

int reconheceL1(char l1[MAX], int l, int r) {
	if (l > r)
		return 1;

	if (l1[l] != l1[r]) 
		return reconheceL1(l1, l + 1, r - 1);
	else
		return 0;
}

int reconheceL2(char l2[MAX], int i, int contA, int contB) {
    if (l2[i] == '\0')
        return contA == contB;

    if (l2[i] == 'a')
        contA++;
    else if (l2[i] == 'b')
        contB++;
    else
        return 0; 

    return reconheceL2(l2, i + 1, contA, contB);
}
