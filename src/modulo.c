#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "modulo.h"

int carregarCarteira(Ativo carteira[], int *totalAtivos, const char *caminhoArquivo) {
    FILE *arquivo = fopen(caminhoArquivo, "r");
    char linha[512];
    int numeroLinha = 0;
    *totalAtivos = 0;
    if (arquivo == NULL) {
        if (errno == ENOENT) {
            puts("Arquivo nao encontrado. Iniciando carteira vazia (mantenha a pasta data).");
            return 1;
        }
        perror("Erro ao abrir a carteira");
        return 0;
    }
    while (fgets(linha, sizeof linha, arquivo)) {
        Ativo ativo;
        char extra;
        FILE *registro;
        int campos, c;
        numeroLinha++;
        if (!strchr(linha, '\n') && !feof(arquivo)) {
            while ((c = fgetc(arquivo)) != '\n' && c != EOF) {}
            printf("Linha %d muito longa; ignorada.\n", numeroLinha);
            continue;
        }
        /* fscanf faz a leitura dos cinco campos em um fluxo limitado a esta linha. */
        registro = tmpfile();
        if (registro == NULL) { perror("Erro no arquivo temporario"); fclose(arquivo); return 0; }
        if (fputs(linha, registro) == EOF || fflush(registro) == EOF) {
            fclose(registro); fclose(arquivo); return 0;
        }
        rewind(registro);
        campos = fscanf(registro, "%49s %49s %d %lf %lf %c", ativo.nome, ativo.categoria,
            &ativo.quantidade, &ativo.precoCompra, &ativo.precoAtual, &extra);
        fclose(registro);
        if (campos == EOF) continue;
        if (campos != 5 || !ativoValido(&ativo)) {
            printf("Registro invalido na linha %d; ignorado.\n", numeroLinha);
            continue;
        }
        if (*totalAtivos >= MAX_ATIVOS) { puts("Limite de 100 ativos atingido; demais registros ignorados."); break; }
        carteira[(*totalAtivos)++] = ativo;
    }
    if (ferror(arquivo)) { perror("Erro durante leitura"); fclose(arquivo); return 0; }
    if (fclose(arquivo) != 0) return 0;
    printf("Dados carregados: %d ativo(s).\n", *totalAtivos);
    return 1;
}

int salvarCarteira(const Ativo carteira[], int totalAtivos, const char *caminhoArquivo) {
    FILE *arquivo = fopen(caminhoArquivo, "w");
    int sucesso = 1;
    if (arquivo == NULL) { perror("Erro ao salvar: confira a pasta data e as permissoes"); return 0; }
    for (int i = 0; i < totalAtivos; i++) {
        if (fprintf(arquivo, "%s %s %d %.2f %.2f\n", carteira[i].nome, carteira[i].categoria,
            carteira[i].quantidade, carteira[i].precoCompra, carteira[i].precoAtual) < 0) {
            sucesso = 0;
            break;
        }
    }
    if (fclose(arquivo) != 0) sucesso = 0;
    puts(sucesso ? "Carteira salva." : "Erro durante gravacao da carteira.");
    return sucesso;
}
