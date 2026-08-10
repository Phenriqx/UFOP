#ifndef BOYER_H
#define BOYER_H

int boyerMoore(char* texto, char* padrao, int n, int m, int *mov);
int boyerMooreOcorrencia(char* texto, char* padrao, int n, int m, int *mov);
int boyerMooreCasamento(char* texto, char* padrao, int n, int m, int *mov);
int boyerMooreHorspool(char* texto, char* padrao, int n, int m, int *mov);
int BHMS(char* texto, char* padrao, int n, int m, int *mov);

#endif
