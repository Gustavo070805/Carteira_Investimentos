#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include "funcoes.h"

/* Retorna 1 para linha completa, -1 para linha longa e 0 para EOF. */
static int lerLinha(const char *mensagem, char *linha, size_t tamanho) {
    int c;
    printf("%s", mensagem);
    fflush(stdout);
    if (!fgets(linha, (int)tamanho, stdin)) return 0;
    if (strchr(linha, '\n')) {
        linha[strcspn(linha, "\r\n")] = '\0';
        return 1;
    }
    c = getchar();
    if (c == EOF || c == '\n') return 1;
    while (c != '\n' && c != EOF) c = getchar();
    puts("Entrada muito longa. Tente novamente.");
    return -1;
}

static int fimValido(const char *fim) {
    while (isspace((unsigned char)*fim)) fim++;
    return *fim == '\0';
}

int lerInteiro(const char *mensagem, int *valor) {
    char linha[128], *fim;
    long numero;
    int estado;
    while ((estado = lerLinha(mensagem, linha, sizeof linha)) != 0) {
        if (estado < 0) continue;
        errno = 0;
        numero = strtol(linha, &fim, 10);
        if (fim != linha && fimValido(fim) && errno != ERANGE &&
            numero >= INT_MIN && numero <= INT_MAX) {
            *valor = (int)numero;
            return 1;
        }
        puts("Informe um numero inteiro valido.");
    }
    return 0;
}

static int lerPreco(const char *mensagem, double *valor, int aceitaZero) {
    char linha[128], *fim;
    double numero;
    int estado;
    while ((estado = lerLinha(mensagem, linha, sizeof linha)) != 0) {
        if (estado < 0) continue;
        errno = 0;
        numero = strtod(linha, &fim);
        if (fim != linha && fimValido(fim) && errno != ERANGE &&
            isfinite(numero) && numero <= 1e12 &&
            (aceitaZero ? numero >= 0.0 : numero >= 0.01)) {
            /* O arquivo utiliza centavos; os calculos usam o mesmo valor salvo. */
            *valor = (double)((long long)(numero * 100.0 + 0.5)) / 100.0;
            return 1;
        }
        puts("Preco invalido. Use ponto decimal, compra >= 0.01 e atual >= 0 (limite 1e12).");
    }
    return 0;
}

static int lerTexto(const char *mensagem, char texto[50]) {
    char linha[128];
    int estado, valido;
    size_t i;
    while ((estado = lerLinha(mensagem, linha, sizeof linha)) != 0) {
        if (estado < 0) continue;
        valido = strlen(linha) > 0 && strlen(linha) < 50;
        for (i = 0; linha[i]; i++)
            if (isspace((unsigned char)linha[i])) valido = 0;
        if (valido) {
            strcpy(texto, linha);
            return 1;
        }
        puts("Use de 1 a 49 caracteres, sem espacos (ex.: RendaFixa).");
    }
    return 0;
}

int ativoValido(const Ativo *ativo) {
    return ativo->nome[0] && ativo->categoria[0] && ativo->quantidade > 0 &&
        isfinite(ativo->precoCompra) && isfinite(ativo->precoAtual) &&
        ativo->precoCompra >= 0.01 && ativo->precoCompra <= 1e12 &&
        ativo->precoAtual >= 0 && ativo->precoAtual <= 1e12;
}

int cadastrarAtivo(Ativo carteira[], int *totalAtivos) {
    Ativo novo;
    if (*totalAtivos >= MAX_ATIVOS) {
        puts("A carteira esta cheia!");
        return 0;
    }
    puts("\n--- Cadastrar ativo ---");
    if (!lerTexto("Nome: ", novo.nome) || !lerTexto("Categoria: ", novo.categoria)) return 0;
    do {
        if (!lerInteiro("Quantidade (inteira e positiva): ", &novo.quantidade)) return 0;
        if (novo.quantidade <= 0) puts("Quantidade deve ser positiva.");
    } while (novo.quantidade <= 0);
    if (!lerPreco("Preco de compra: ", &novo.precoCompra, 0) ||
        !lerPreco("Preco atual: ", &novo.precoAtual, 1)) return 0;
    carteira[(*totalAtivos)++] = novo;
    puts("Ativo cadastrado com sucesso!");
    return 1;
}

double calcularRentabilidade(double compra, double atual) {
    if (compra <= 0) return 0;
    return (atual - compra) / compra * 100.0;
}

double calcularLucro(double compra, double atual, int quantidade) {
    return (atual - compra) * quantidade;
}

const char *classificarRisco(double rentabilidade) {
    if (rentabilidade < -10) return "alto";
    else if (rentabilidade < 0) return "moderado";
    else return "baixo";
}

double obterCustoTotal(const Ativo carteira[], int totalAtivos) {
    double total = 0;
    for (int i = 0; i < totalAtivos; i++) total += carteira[i].quantidade * carteira[i].precoCompra;
    return total;
}

double obterValorTotal(const Ativo carteira[], int totalAtivos) {
    double total = 0;
    for (int i = 0; i < totalAtivos; i++) total += carteira[i].quantidade * carteira[i].precoAtual;
    return total;
}

void listarAtivos(const Ativo carteira[], int totalAtivos) {
    if (!totalAtivos) { puts("A carteira esta vazia."); return; }
    for (int i = 0; i < totalAtivos; i++) {
        double r = calcularRentabilidade(carteira[i].precoCompra, carteira[i].precoAtual);
        printf("%d. %s (%s) | Qtd: %d | Compra: R$ %.2f | Atual: R$ %.2f\n",
            i + 1, carteira[i].nome, carteira[i].categoria, carteira[i].quantidade,
            carteira[i].precoCompra, carteira[i].precoAtual);
        printf("   Rentabilidade: %.2f%% | Lucro/prejuizo: R$ %.2f | Risco didatico: %s\n",
            r, calcularLucro(carteira[i].precoCompra, carteira[i].precoAtual, carteira[i].quantidade),
            classificarRisco(r));
    }
    puts("Risco didatico do CP1: < -10% alto; de -10% a < 0% moderado; >= 0% baixo.");
    puts("Essa regra baseada no desempenho passado NAO mede o risco real de um investimento.");
}

void calcularValorTotal(const Ativo carteira[], int totalAtivos) {
    printf("Valor total atual da carteira: R$ %.2f\n", obterValorTotal(carteira, totalAtivos));
}

void calcularRentabilidadeGeral(const Ativo carteira[], int totalAtivos) {
    double custo = obterCustoTotal(carteira, totalAtivos);
    double atual = obterValorTotal(carteira, totalAtivos);
    if (!totalAtivos || custo <= 0) { puts("Sem custo positivo para calcular rentabilidade."); return; }
    printf("Custo total de aquisicao: R$ %.2f\nValor atualizado: R$ %.2f\n", custo, atual);
    printf("Rentabilidade geral: %.2f%%\nLucro/prejuizo total: R$ %.2f\n",
        calcularRentabilidade(custo, atual), atual - custo);
}

void ordenarPorRentabilidade(Ativo carteira[], int totalAtivos) {
    /* Bubble sort decrescente; empates preservam a ordem anterior. */
    for (int i = 0; i < totalAtivos - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < totalAtivos - 1 - i; j++) {
            if (calcularRentabilidade(carteira[j].precoCompra, carteira[j].precoAtual) <
                calcularRentabilidade(carteira[j+1].precoCompra, carteira[j+1].precoAtual)) {
                Ativo auxiliar = carteira[j];
                carteira[j] = carteira[j+1];
                carteira[j+1] = auxiliar;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }
}

void simuladorEducativo(const Ativo carteira[], int totalAtivos) {
    double inicial = obterValorTotal(carteira, totalAtivos);
    double poupanca = inicial, tesouro = inicial, cdb = inicial;
    if (inicial <= 0) { puts("Cadastre ativos com valor atual total positivo para simular."); return; }
    puts("\n=== SIMULADOR EDUCATIVO ===");
    printf("E se R$ %.2f fossem investidos por %d meses?\n", inicial, MESES_SIMULACAO);
    for (int mes = 0; mes < MESES_SIMULACAO; mes++) {
        poupanca *= 1 + TAXA_POUPANCA;
        tesouro *= 1 + TAXA_TESOURO_SELIC;
        cdb *= 1 + TAXA_CDB;
    }
    printf("POUPANCA      (%.2f%%/mes): R$ %.2f (+R$ %.2f)\n", TAXA_POUPANCA*100, poupanca, poupanca-inicial);
    printf("TESOURO SELIC (%.2f%%/mes): R$ %.2f (+R$ %.2f)\n", TAXA_TESOURO_SELIC*100, tesouro, tesouro-inicial);
    printf("CDB           (%.2f%%/mes): R$ %.2f (+R$ %.2f)\n", TAXA_CDB*100, cdb, cdb-inicial);
    puts("Rentabilidade e quanto o dinheiro ganha ou perde em relacao ao valor inicial.");
    puts("Juros compostos: a cada mes, o rendimento tambem passa a render.");
    puts("Risco e a possibilidade de perda ou de nao recuperar o dinheiro quando precisar.");
    puts("Poupanca: nesta comparacao, foi usada a menor taxa ilustrativa.");
    puts("Tesouro Selic: representa um titulo publico; preco e regras de resgate importam.");
    puts("CDB: representa um titulo bancario; emissor, prazo e liquidez importam.");
    puts("Liquidez significa a facilidade de transformar o investimento em dinheiro disponivel.");
    puts("Taxas FIXAS e ILUSTRATIVAS: nao sao cotacoes, promessas ou recomendacoes.");
    puts("Simulacao bruta: sem impostos, taxas, inflacao, aportes ou retiradas.");
}

void gerarRelatorioFinal(Ativo carteira[], int totalAtivos) {
    puts("\n=== RELATORIO FINAL ===");
    ordenarPorRentabilidade(carteira, totalAtivos);
    puts("Ativos ordenados do melhor para o pior desempenho:");
    listarAtivos(carteira, totalAtivos);
    calcularValorTotal(carteira, totalAtivos);
    calcularRentabilidadeGeral(carteira, totalAtivos);
    if (!totalAtivos) puts("Lucro/prejuizo total: R$ 0.00 | Rentabilidade: nao aplicavel.");
    puts("\nImpacto social - inclusao financeira (ODS 8.10):");
    puts("O simulador busca aproximar iniciantes dos conceitos de investimento, mostrando");
    puts("em linguagem simples como o tempo e os juros afetam o dinheiro. A comparacao");
    puts("educativa incentiva escolhas informadas e a compreensao de risco e liquidez,");
    puts("sem substituir orientacao profissional nem garantir resultados futuros.");
}
