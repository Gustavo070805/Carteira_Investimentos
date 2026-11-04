#include <stdio.h>
#include "funcoes.h"
#include "modulo.h"

int main(void) {
    Ativo carteira[MAX_ATIVOS];
    int totalAtivos = 0;
    int opcao = -1;
    const char *caminho = "data/carteira.txt";

    /* Evita sobrescrever um arquivo que nao pode ser lido por erro de acesso. */
    if (!carregarCarteira(carteira, &totalAtivos, caminho)) return 1;
    while (opcao != 0) {
        puts("\n=== CARTEIRA DE INVESTIMENTOS ===");
        puts("1. Cadastrar ativo\n2. Listar ativos\n3. Valor total da carteira");
        puts("4. Rentabilidade geral\n5. Ordenar por rentabilidade");
        puts("6. Simulador educativo\n7. Relatorio final\n0. Sair");
        if (!lerInteiro("Escolha: ", &opcao)) {
            puts("\nEntrada encerrada. Salvando a carteira...");
            return salvarCarteira(carteira, totalAtivos, caminho) ? 0 : 1;
        }
        switch (opcao) {
            case 1:
                if (cadastrarAtivo(carteira, &totalAtivos))
                    salvarCarteira(carteira, totalAtivos, caminho);
                break;
            case 2: listarAtivos(carteira, totalAtivos); break;
            case 3: calcularValorTotal(carteira, totalAtivos); break;
            case 4: calcularRentabilidadeGeral(carteira, totalAtivos); break;
            case 5:
                ordenarPorRentabilidade(carteira, totalAtivos);
                listarAtivos(carteira, totalAtivos);
                salvarCarteira(carteira, totalAtivos, caminho);
                break;
            case 6: simuladorEducativo(carteira, totalAtivos); break;
            case 7:
                gerarRelatorioFinal(carteira, totalAtivos);
                salvarCarteira(carteira, totalAtivos, caminho);
                break;
            case 0:
                if (!salvarCarteira(carteira, totalAtivos, caminho)) return 1;
                puts("Encerrando o programa...");
                break;
            default: puts("Opcao invalida. Tente novamente.");
        }
    }
    return 0;
}
