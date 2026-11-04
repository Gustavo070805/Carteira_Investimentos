#ifndef MODULO_H
#define MODULO_H
#include "funcoes.h"
int carregarCarteira(Ativo carteira[], int *totalAtivos, const char *caminhoArquivo);
int salvarCarteira(const Ativo carteira[], int totalAtivos, const char *caminhoArquivo);
#endif
