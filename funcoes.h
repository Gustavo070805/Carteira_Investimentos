#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_ATIVOS 100
#define TAXA_POUPANCA 0.005
#define TAXA_TESOURO_SELIC 0.008
#define TAXA_CDB 0.009
#define MESES_SIMULACAO 12

typedef struct Ativo {
    char nome[50];
    char categoria[50];
    int quantidade;
    double precoCompra;
    double precoAtual;
} Ativo;

int lerInteiro(const char *mensagem, int *valor);
int ativoValido(const Ativo *ativo);
int cadastrarAtivo(Ativo carteira[], int *totalAtivos);
double calcularRentabilidade(double compra, double atual);
double calcularLucro(double compra, double atual, int quantidade);
const char *classificarRisco(double rentabilidade);
double obterCustoTotal(const Ativo carteira[], int totalAtivos);
double obterValorTotal(const Ativo carteira[], int totalAtivos);
void listarAtivos(const Ativo carteira[], int totalAtivos);
void calcularValorTotal(const Ativo carteira[], int totalAtivos);
void calcularRentabilidadeGeral(const Ativo carteira[], int totalAtivos);
void ordenarPorRentabilidade(Ativo carteira[], int totalAtivos);
void simuladorEducativo(const Ativo carteira[], int totalAtivos);
void gerarRelatorioFinal(Ativo carteira[], int totalAtivos);
#endif
