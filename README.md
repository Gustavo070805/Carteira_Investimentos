# Carteira de Investimentos — Checkpoint 3

## Descrição do projeto

Aplicação acadêmica de terminal desenvolvida em C para gerenciar uma carteira de investimentos e apresentar conceitos financeiros em linguagem simples. O tema do trabalho é inclusão financeira, associado pelo enunciado à ODS 8.10 da ONU.

O objetivo é aproximar iniciantes de conceitos como rentabilidade, lucro/prejuízo, risco e juros compostos, enquanto o grupo aplica funções, modularização, estruturas, vetores, arquivos e ordenação.

Esta versão integra a evolução dos três checkpoints. Os dados e as taxas são didáticos: não há conexão com corretoras, consulta de cotações ou recomendação de investimento.

## Público-alvo

- Pessoas iniciantes que desejam entender a organização de uma carteira e comparar cenários educativos.
- Estudantes de programação em C.
- Professores e avaliadores do projeto interdisciplinar.

## Funcionalidades do sistema

- Cadastrar até 100 ativos: nome, categoria, quantidade inteira, preço de compra e preço atual por unidade.
- Listar os ativos com rentabilidade individual, lucro/prejuízo e classificação didática de risco herdada do CP1.
- Calcular o valor total atual e o custo total da carteira.
- Calcular a rentabilidade geral e o lucro/prejuízo total.
- Ordenar os ativos por rentabilidade percentual, do melhor para o pior, usando bubble sort.
- Simular o investimento do valor atual total da carteira por 12 meses em três cenários ilustrativos.
- Exibir no terminal um relatório final com ativos ordenados, totais e um parágrafo sobre impacto social.
- Carregar e salvar os dados em `data/carteira.txt`.
- Validar entradas de cadastro, limites e valores não finitos, como `nan` e `inf`.

### Menu

```text
=== CARTEIRA DE INVESTIMENTOS ===
1. Cadastrar ativo
2. Listar ativos
3. Valor total da carteira
4. Rentabilidade geral
5. Ordenar por rentabilidade
6. Simulador educativo
7. Relatorio final
0. Sair
```

### Evolução dos checkpoints

| Etapa | Implementação |
|---|---|
| CP1 | Funções com retorno e `void`, menu com `while` e `switch`, rentabilidade, lucro/prejuízo e risco com `if/else` |
| CP2 | `struct Ativo`, vetor de estruturas, funções que recebem o vetor e persistência em texto |
| CP3 | Ordenação decrescente, simulador de 12 meses e relatório final |

As restrições de um único ativo, sem `struct` e sem arquivos pertenciam ao CP1. A versão final utiliza a estrutura e a persistência exigidas a partir do CP2. Os cálculos individuais e a regra didática de risco do CP1 estão disponíveis na listagem e no relatório; o menu segue o modelo final do CP3.

## Tecnologias utilizadas no desenvolvimento

- Linguagem C, padrão C99 ou posterior.
- Biblioteca padrão de C: entrada e saída, conversão e validação de dados, strings e verificação de valores finitos.
- `struct Ativo` e vetor de até 100 estruturas.
- Funções, ponteiros e arquivos de cabeçalho para modularização.
- Bubble sort com interrupção antecipada quando não há trocas.
- Arquivo texto, com `fopen`, `fscanf`, `fprintf` e `fclose`.
- GCC para compilação.

Os preços usam `double` e são gravados com duas casas decimais. O projeto não exige bibliotecas externas, banco de dados ou interface gráfica.

## Requisitos mínimos para execução

- Computador com terminal e GCC instalado, com suporte a C99 ou posterior.
- No Windows, GCC acessível pelo terminal, por exemplo mediante instalação do MinGW-w64.
- Pastas e arquivos organizados conforme a estrutura abaixo.
- Permissão para ler e gravar na pasta `data` e criar arquivos temporários no sistema, usados na leitura dos registros.
- Não é necessária conexão com a internet para executar o programa.

Não foram aferidos requisitos mínimos específicos de RAM, processador ou armazenamento.

## Estrutura de pastas

```text
meu-projeto-c/
├── src/
│   ├── main.c
│   ├── funcoes.c
│   └── modulo.c
├── include/
│   ├── funcoes.h
│   └── modulo.h
├── data/
│   └── carteira.txt
├── README.md
├── TESTES.md
├── ROTEIRO_VIDEO.md
└── RELATORIO_EXEMPLO.txt
```

| Arquivo | Responsabilidade |
|---|---|
| `main.c` | Menu, inicialização e integração das operações |
| `funcoes.c` | Entrada validada, cadastro, listagem, cálculos, ordenação, simulador e relatório |
| `funcoes.h` | Estrutura `Ativo`, constantes e protótipos |
| `modulo.c` | Leitura e gravação do arquivo de dados |
| `modulo.h` | Protótipos da persistência |
| `carteira.txt` | Três ativos de exemplo, sem representar recomendação |
| `TESTES.md` | Resumo dos testes executados no ambiente de geração |
| `ROTEIRO_VIDEO.md` | Sugestão de demonstração sem narração |
| `RELATORIO_EXEMPLO.txt` | Saída de exemplo da opção 7, para consulta |

## Instruções para execução

### 1. Extraia o projeto e abra o terminal na raiz

A pasta atual deve conter os diretórios `src`, `include` e `data`. O caminho `data/carteira.txt` é relativo ao diretório de execução.

### 2. Compile

Linux ou macOS com GCC:

```bash
gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c src/modulo.c -o programa
```

Windows com GCC:

```bash
gcc -Wall -Wextra -Iinclude src/main.c src/funcoes.c src/modulo.c -o programa.exe
```

Opcionalmente acrescente `-std=c99` para selecionar explicitamente o padrão. Os arquivos `.c` são compilados separadamente; o `main.c` inclui apenas os cabeçalhos, não os outros arquivos `.c`.

### 3. Execute

Linux/macOS:

```bash
./programa
```

Windows, pelo PowerShell:

```powershell
.\programa.exe
```

### 4. Use o sistema

1. Liste os três ativos de exemplo com a opção `2`.
2. Consulte valor total e rentabilidade com as opções `3` e `4`.
3. Use `5` para ordenar do maior para o menor percentual de rentabilidade.
4. Use `6` para comparar os cenários educativos.
5. Use `7` para exibir o relatório final no terminal.
6. Use `1` para cadastrar outro ativo e `0` para salvar e sair.

A ordenação e o relatório reorganizam o vetor e salvam essa ordem. O relatório exibido no terminal não é exportado automaticamente para um arquivo; `RELATORIO_EXEMPLO.txt` é apenas uma captura fornecida com a entrega.

### Regras de cadastro

- Nome e categoria: de 1 a 49 caracteres, sem espaços. Exemplo: `TesouroDireto` e `RendaFixa`.
- Quantidade: inteiro positivo, dentro da faixa de `int` do ambiente.
- Preço de compra: no mínimo `0.01`; preço atual: no mínimo `0`.
- Preços: no máximo `1000000000000`, com ponto decimal. O cadastro arredonda para centavos.
- Entradas inválidas são solicitadas novamente. Um cadastro interrompido pelo fim da entrada não é adicionado.
- Registros com o mesmo nome podem ser cadastrados separadamente; não há consolidação automática.

## Persistência dos dados

Formato de `data/carteira.txt`, um registro por linha:

```text
nome categoria quantidade precoCompra precoAtual
```

Dados de exemplo:

```text
PETR4 Acao 100 35.50 38.20
KNRI11 FII 10 155.00 160.00
TesouroDireto RendaFixa 5 100.00 105.50
```

Os registros são carregados ao iniciar. Linhas inválidas são informadas e ignoradas; registros além do limite de 100 não são carregados. O programa verifica falhas na abertura, leitura e gravação.

Se o arquivo não existir, a carteira começa vazia. A pasta `data` precisa existir para salvar. Os dados são salvos após cadastro, ordenação, relatório e ao sair, inclusive quando a entrada padrão termina. A gravação reescreve o arquivo com os dados válidos em memória: faça uma cópia antes de editar manualmente ou testar arquivos inválidos. Não há backup automático nem proteção contra interrupção durante a gravação.

## Fórmulas utilizadas

```text
Rentabilidade individual (%) = (precoAtual - precoCompra) / precoCompra * 100
Lucro/prejuizo individual = (precoAtual - precoCompra) * quantidade
Custo total = soma de (quantidade * precoCompra)
Valor atual total = soma de (quantidade * precoAtual)
Rentabilidade geral (%) = (valorAtualTotal - custoTotal) / custoTotal * 100
Lucro/prejuizo total = valorAtualTotal - custoTotal
```

A rentabilidade geral considera os totais investidos, não a média simples dos percentuais individuais. Se não houver custo positivo, a rentabilidade não é calculada.

### Classificação didática de risco

| Rentabilidade individual | Risco didático |
|---|---|
| Menor que -10% | Alto |
| De -10% até abaixo de 0% | Moderado |
| Igual ou maior que 0% | Baixo |

Essa regra foi mantida do exercício do CP1. Ela não mede o risco real de um investimento: desempenho positivo não garante segurança.

## Simulador educativo

O capital inicial é o valor atual total da carteira. Para cada cenário, um `for` aplica juros compostos durante 12 meses, sem aportes ou retiradas:

```text
valor = capitalInicial
repetir 12 vezes: valor = valor * (1 + taxaMensal)
ganho = valor - capitalInicial
```

As constantes ficam em `include/funcoes.h`:

| Constante | Taxa mensal ilustrativa |
|---|---|
| `TAXA_POUPANCA` | 0,50% |
| `TAXA_TESOURO_SELIC` | 0,80% |
| `TAXA_CDB` | 0,90% |
| `MESES_SIMULACAO` | 12 meses |

As taxas são hipóteses fixas do exercício, não taxas atuais, regras oficiais dos produtos ou promessas de retorno. O cenário de CDB não calcula CDI nem uma equivalência real a 110% do CDI. A simulação é bruta e desconsidera impostos, taxas e inflação. O programa explica rentabilidade, juros compostos, risco e liquidez em linguagem simples.

## Resultado esperado com os dados fornecidos

| Indicador | Resultado |
|---|---|
| Custo total | R$ 5.600,00 |
| Valor atual total | R$ 5.947,50 |
| Lucro total | R$ 347,50 |
| Rentabilidade geral | 6,21% |

Ordem esperada: `PETR4` (7,61%), `TesouroDireto` (5,50%) e `KNRI11` (3,23%).

## Impacto social

O simulador busca contribuir para a inclusão financeira ao traduzir conceitos de investimento em comparações compreensíveis. Mostrar o efeito do tempo e dos juros ajuda iniciantes a formular perguntas sobre retorno, risco e acesso ao próprio dinheiro. Essa proposta dialoga com o tema da ODS 8.10 indicado na atividade, sem substituir educação financeira mais ampla ou orientação profissional e sem demonstrar, por si só, impacto social mensurado.

## Vídeo de demonstração

Link: PENDENTE — inserir aqui o endereço do vídeo não listado no YouTube ou compartilhado pelo Google Drive.

O vídeo deve durar de 2 a 3 minutos e não deve ter narração. Há uma sugestão de sequência em `ROTEIRO_VIDEO.md`. Não inclua o arquivo de vídeo no ZIP. A gravação, publicação e substituição deste campo precisam ser realizadas pelo grupo antes da entrega.

## Entrega e apresentação

- Revisar o código e executar os testes no computador usado na apresentação.
- Conferir os nomes e RAs da equipe.
- Publicar o vídeo e atualizar o link acima.
- Compactar fontes, cabeçalhos, dados de exemplo e documentação em ZIP.
- Enviar pelo grupo do Blackboard, conforme a atividade.
- Apresentação presencial: Aula 12, em 04/11, conforme o enunciado recebido.

## Limitações

- Não há edição ou exclusão de ativos pelo menu.
- Quantidades fracionárias não são aceitas.
- Não há cotações em tempo real, autenticação, criptografia ou integração bancária.
- Valores usam ponto flutuante; trata-se de uma aplicação didática, não de um sistema contábil de produção.
- A classificação de risco e as taxas do simulador são simplificações educativas.

## Desenvolvedores

Equipe reproduzida do README de referência fornecido; confirmar antes da entrega:

| Nome completo | RGM |
|---|---|
| Emilly Larissa Machado Silva | 49706713 |
| Guilherme Yoshio da Silva Shibata | 47787520 |
| Gustavo Candile Monteiro Barbosa | 47174501 |
| Guilherme Roger Lourenço Pereira | 47370190 |
| Allan Hidalgo de Carvalho | 48398675 | 
