#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define MAX_NOME 30
#define MAX_TIPO 20

// ============================================
// ESTRUTURA DE DADOS
// ============================================

/**
 * Estrutura Componente
 * Representa cada peça necessária para montar a torre de fuga
 * - nome: identificação do componente
 * - tipo: categoria do componente (controle, suporte, propulsão)
 * - prioridade: importância de 1 a 10 (10 = mais crítico)
 */
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Componente;

// ============================================
// VARIÁVEIS GLOBAIS
// ============================================
Componente componentes[MAX_COMPONENTES];
int totalComponentes = 0;

// Contadores de comparações para cada algoritmo
int comparacoesBubble = 0;
int comparacoesInsertion = 0;
int comparacoesSelection = 0;
int comparacoesBuscaBinaria = 0;

// ============================================
// PROTÓTIPOS DAS FUNÇÕES
// ============================================

// Algoritmos de ordenação
void bubbleSortNome(Componente vetor[], int n);
void insertionSortTipo(Componente vetor[], int n);
void selectionSortPrioridade(Componente vetor[], int n);

// Busca
int buscaBinariaPorNome(Componente vetor[], int n, char nomeBusca[]);

// Utilitários
void cadastrarComponente();
void listarComponentes(Componente vetor[], int n, char titulo[]);
void exibirMenu();
void limparBuffer();
void pausar();
void copiarVetor(Componente origem[], Componente destino[], int n);

// Medição de desempenho
void medirTempo(void (*algoritmo)(Componente[], int), Componente vetor[], int n, char nomeAlgoritmo[]);

// ============================================
// IMPLEMENTAÇÃO - ALGORITMOS DE ORDENAÇÃO
// ============================================

/**
 * Função: bubbleSortNome
 * Descrição: Ordena componentes por nome usando Bubble Sort
 * Complexidade: O(n²) no pior caso
 * Característica: Algoritmo mais simples, mas ineficiente para dados grandes
 * Contador: comparacoesBubble incrementa a cada comparação
 */
void bubbleSortNome(Componente vetor[], int n) {
    comparacoesBubble = 0;
    Componente temp;
    
    printf("\n🔄 ORDENANDO POR NOME (BUBBLE SORT)...\n");
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoesBubble++; // Conta cada comparação
            if (strcasecmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                // Troca os elementos
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    
    printf("✅ Ordenação concluída!\n");
    printf("📊 Comparações realizadas: %d\n", comparacoesBubble);
}

/**
 * Função: insertionSortTipo
 * Descrição: Ordena componentes por tipo usando Insertion Sort
 * Complexidade: O(n²) no pior caso, O(n) no melhor caso
 * Característica: Eficiente para dados parcialmente ordenados
 * Contador: comparacoesInsertion incrementa a cada comparação
 */
void insertionSortTipo(Componente vetor[], int n) {
    comparacoesInsertion = 0;
    Componente chave;
    int j;
    
    printf("\n🔄 ORDENANDO POR TIPO (INSERTION SORT)...\n");
    
    for (int i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;
        
        while (j >= 0) {
            comparacoesInsertion++; // Conta cada comparação
            if (strcasecmp(vetor[j].tipo, chave.tipo) <= 0) {
                break;
            }
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
    
    printf("✅ Ordenação concluída!\n");
    printf("📊 Comparações realizadas: %d\n", comparacoesInsertion);
}

/**
 * Função: selectionSortPrioridade
 * Descrição: Ordena componentes por prioridade usando Selection Sort
 * Complexidade: O(n²) em todos os casos
 * Característica: Sempre faz o mesmo número de comparações
 * Contador: comparacoesSelection incrementa a cada comparação
 */
void selectionSortPrioridade(Componente vetor[], int n) {
    comparacoesSelection = 0;
    Componente temp;
    int posicaoMenor;
    
    printf("\n🔄 ORDENANDO POR PRIORIDADE (SELECTION SORT)...\n");
    
    for (int i = 0; i < n - 1; i++) {
        posicaoMenor = i;
        for (int j = i + 1; j < n; j++) {
            comparacoesSelection++; // Conta cada comparação
            if (vetor[j].prioridade < vetor[posicaoMenor].prioridade) {
                posicaoMenor = j;
            }
        }
        if (posicaoMenor != i) {
            temp = vetor[i];
            vetor[i] = vetor[posicaoMenor];
            vetor[posicaoMenor] = temp;
        }
    }
    
    printf("✅ Ordenação concluída!\n");
    printf("📊 Comparações realizadas: %d\n", comparacoesSelection);
}

// ============================================
// IMPLEMENTAÇÃO - BUSCA BINÁRIA
// ============================================

/**
 * Função: buscaBinariaPorNome
 * Descrição: Busca um componente pelo nome usando busca binária
 * Pré-requisito: Vetor deve estar ordenado por nome
 * Complexidade: O(log n)
 * Retorno: Índice do componente encontrado, -1 se não encontrado
 * Contador: comparacoesBuscaBinaria incrementa a cada comparação
 */
int buscaBinariaPorNome(Componente vetor[], int n, char nomeBusca[]) {
    comparacoesBuscaBinaria = 0;
    int esquerda = 0;
    int direita = n - 1;
    int meio;
    
    printf("\n🔍 BUSCA BINÁRIA POR NOME\n");
    printf("--------------------------\n");
    printf("Procurando por: %s\n", nomeBusca);
    
    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;
        comparacoesBuscaBinaria++;
        
        int comparacao = strcasecmp(vetor[meio].nome, nomeBusca);
        
        if (comparacao == 0) {
            printf("✅ Componente encontrado na posição %d!\n", meio + 1);
            printf("📊 Comparações realizadas: %d\n", comparacoesBuscaBinaria);
            return meio;
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    printf("❌ Componente não encontrado!\n");
    printf("📊 Comparações realizadas: %d\n", comparacoesBuscaBinaria);
    return -1;
}

// ============================================
// IMPLEMENTAÇÃO - UTILITÁRIOS
// ============================================

/**
 * Função: cadastrarComponente
 * Descrição: Cadastra um novo componente no sistema
 * Validações: Limite máximo de 20 componentes
 */
void cadastrarComponente() {
    if (totalComponentes >= MAX_COMPONENTES) {
        printf("\n❌ Limite máximo de %d componentes atingido!\n", MAX_COMPONENTES);
        return;
    }
    
    printf("\n📦 CADASTRO DE COMPONENTE\n");
    printf("--------------------------\n");
    printf("Componente %d de %d\n", totalComponentes + 1, MAX_COMPONENTES);
    printf("\n");
    
    limparBuffer();
    
    printf("Nome do componente: ");
    fgets(componentes[totalComponentes].nome, MAX_NOME, stdin);
    componentes[totalComponentes].nome[strcspn(componentes[totalComponentes].nome, "\n")] = '\0';
    
    printf("Tipo (controle/suporte/propulsao/estrutura): ");
    fgets(componentes[totalComponentes].tipo, MAX_TIPO, stdin);
    componentes[totalComponentes].tipo[strcspn(componentes[totalComponentes].tipo, "\n")] = '\0';
    
    printf("Prioridade (1 a 10): ");
    scanf("%d", &componentes[totalComponentes].prioridade);
    
    // Valida prioridade
    while (componentes[totalComponentes].prioridade < 1 || componentes[totalComponentes].prioridade > 10) {
        printf("❌ Prioridade deve ser entre 1 e 10. Digite novamente: ");
        scanf("%d", &componentes[totalComponentes].prioridade);
    }
    
    totalComponentes++;
    printf("\n✅ Componente cadastrado com sucesso!\n");
}

/**
 * Função: copiarVetor
 * Descrição: Copia um vetor de componentes para outro
 * Útil para preservar o vetor original durante ordenações
 */
void copiarVetor(Componente origem[], Componente destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

/**
 * Função: listarComponentes
 * Descrição: Exibe todos os componentes formatados
 * Parâmetros: vetor, tamanho, título personalizado
 */
void listarComponentes(Componente vetor[], int n, char titulo[]) {
    printf("\n%s\n", titulo);
    printf("========================================\n");
    
    if (n == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    
    printf("%-3s | %-25s | %-12s | %-10s\n", 
           "#", "NOME", "TIPO", "PRIORIDADE");
    printf("----|---------------------------|--------------|------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-3d | %-25s | %-12s | %-10d\n",
               i + 1,
               vetor[i].nome,
               vetor[i].tipo,
               vetor[i].prioridade);
    }
}

/**
 * Função: limparBuffer
 * Descrição: Remove caracteres pendentes no buffer de entrada
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/**
 * Função: pausar
 * Descrição: Aguarda o usuário pressionar Enter
 */
void pausar() {
    printf("\nPressione Enter para continuar...");
    limparBuffer();
}

// ============================================
// IMPLEMENTAÇÃO - MEDIÇÃO DE DESEMPENHO
// ============================================

/**
 * Função: medirTempo
 * Descrição: Mede o tempo de execução de um algoritmo de ordenação
 * Parâmetros:
 *   - algoritmo: ponteiro para função de ordenação
 *   - vetor: vetor a ser ordenado
 *   - n: tamanho do vetor
 *   - nomeAlgoritmo: nome para exibição
 * 
 * Uso: clock() para medir tempo em microssegundos
 */
void medirTempo(void (*algoritmo)(Componente[], int), 
                Componente vetor[], int n, char nomeAlgoritmo[]) {
    clock_t inicio, fim;
    double tempo_gasto;
    
    // Cria uma cópia do vetor para não modificar o original
    Componente copia[MAX_COMPONENTES];
    copiarVetor(vetor, copia, n);
    
    printf("\n⏱️ MEDINDO DESEMPENHO - %s\n", nomeAlgoritmo);
    printf("====================================\n");
    printf("Tamanho do vetor: %d elementos\n", n);
    
    // Mede o tempo de execução
    inicio = clock();
    algoritmo(copia, n);
    fim = clock();
    
    tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("⏱️ Tempo de execução: %.6f segundos\n", tempo_gasto);
    printf("📊 Comparações: ");
    
    // Exibe o contador correspondente
    if (strstr(nomeAlgoritmo, "Bubble") != NULL) {
        printf("%d\n", comparacoesBubble);
    } else if (strstr(nomeAlgoritmo, "Insertion") != NULL) {
        printf("%d\n", comparacoesInsertion);
    } else if (strstr(nomeAlgoritmo, "Selection") != NULL) {
        printf("%d\n", comparacoesSelection);
    }
    
    // Mostra o vetor ordenado
    listarComponentes(copia, n, "📋 VETOR ORDENADO:");
}

// ============================================
// FUNÇÕES DO MENU
// ============================================

/**
 * Função: exibirComponentesChave
 * Descrição: Exibe os componentes mais críticos (prioridade >= 8)
 */
void exibirComponentesChave() {
    printf("\n🔑 COMPONENTES-CHAVE (PRIORIDADE ALTA)\n");
    printf("=======================================\n");
    
    int encontrou = 0;
    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].prioridade >= 8) {
            printf("  🏆 %s (Tipo: %s, Prioridade: %d)\n",
                   componentes[i].nome,
                   componentes[i].tipo,
                   componentes[i].prioridade);
            encontrou = 1;
        }
    }
    
    if (!encontrou) {
        printf("Nenhum componente com prioridade alta encontrado.\n");
        printf("💡 Dica: Cadastre componentes com prioridade >= 8!\n");
    }
}

/**
 * Função: simularMontagemTorre
 * Descrição: Simula a montagem da torre com os componentes ordenados
 */
void simularMontagemTorre() {
    if (totalComponentes == 0) {
        printf("\n❌ Nenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n🏗️ MONTAGEM DA TORRE DE FUGA\n");
    printf("==============================\n");
    printf("🎯 Estratégia: Prioridade (do mais crítico ao menos crítico)\n\n");
    
    // Cria cópia e ordena por prioridade (decrescente)
    Componente copia[MAX_COMPONENTES];
    copiarVetor(componentes, copia, totalComponentes);
    
    // Ordenação por prioridade (Selection Sort)
    for (int i = 0; i < totalComponentes - 1; i++) {
        int posMaior = i;
        for (int j = i + 1; j < totalComponentes; j++) {
            if (copia[j].prioridade > copia[posMaior].prioridade) {
                posMaior = j;
            }
        }
        if (posMaior != i) {
            Componente temp = copia[i];
            copia[i] = copia[posMaior];
            copia[posMaior] = temp;
        }
    }
    
    printf("📋 ORDEM DE MONTAGEM (Prioridade Decrescente):\n");
    printf("===============================================\n");
    printf("%-3s | %-25s | %-12s | %-10s\n", 
           "#", "NOME", "TIPO", "PRIORIDADE");
    printf("----|---------------------------|--------------|------------\n");
    
    for (int i = 0; i < totalComponentes; i++) {
        printf("%-3d | %-25s | %-12s | %-10d",
               i + 1,
               copia[i].nome,
               copia[i].tipo,
               copia[i].prioridade);
        
        // Marca componentes críticos
        if (copia[i].prioridade >= 8) {
            printf(" ⚡");
        }
        printf("\n");
    }
    
    printf("\n✅ Torre de fuga montada com sucesso!\n");
    printf("🚀 Pronto para decolagem!\n");
}

/**
 * Função: exibirMenuOrdenacao
 * Descrição: Menu para escolher algoritmo de ordenação
 */
void exibirMenuOrdenacao() {
    if (totalComponentes == 0) {
        printf("\n❌ Nenhum componente cadastrado!\n");
        printf("Por favor, cadastre componentes primeiro.\n");
        return;
    }
    
    int opcao;
    Componente copia[MAX_COMPONENTES];
    
    do {
        printf("\n🔄 ALGORITMOS DE ORDENAÇÃO\n");
        printf("===========================\n");
        printf("1. Bubble Sort - Ordenar por NOME\n");
        printf("2. Insertion Sort - Ordenar por TIPO\n");
        printf("3. Selection Sort - Ordenar por PRIORIDADE\n");
        printf("4. Comparar TODOS os algoritmos\n");
        printf("0. Voltar ao menu principal\n");
        printf("===========================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                copiarVetor(componentes, copia, totalComponentes);
                medirTempo(bubbleSortNome, copia, totalComponentes, "Bubble Sort (Nome)");
                pausar();
                break;
                
            case 2:
                copiarVetor(componentes, copia, totalComponentes);
                medirTempo(insertionSortTipo, copia, totalComponentes, "Insertion Sort (Tipo)");
                pausar();
                break;
                
            case 3:
                copiarVetor(componentes, copia, totalComponentes);
                medirTempo(selectionSortPrioridade, copia, totalComponentes, "Selection Sort (Prioridade)");
                pausar();
                break;
                
            case 4: {
                printf("\n📊 COMPARAÇÃO COMPLETA DE DESEMPENHO\n");
                printf("=====================================\n\n");
                
                // Bubble Sort
                printf("🔵 BUBBLE SORT (Nome):\n");
                copiarVetor(componentes, copia, totalComponentes);
                medirTempo(bubbleSortNome, copia, totalComponentes, "Bubble Sort");
                printf("\n");
                
                // Insertion Sort
                printf("🟢 INSERTION SORT (Tipo):\n");
                copiarVetor(componentes, copia, totalComponentes);
                medirTempo(insertionSortTipo, copia, totalComponentes, "Insertion Sort");
                printf("\n");
                
                // Selection Sort
                printf("🔴 SELECTION SORT (Prioridade):\n");
                copiarVetor(componentes, copia, totalComponentes);
                medirTempo(selectionSortPrioridade, copia, totalComponentes, "Selection Sort");
                printf("\n");
                
                printf("📌 ANÁLISE COMPARATIVA:\n");
                printf("  - Bubble Sort: %d comparações\n", comparacoesBubble);
                printf("  - Insertion Sort: %d comparações\n", comparacoesInsertion);
                printf("  - Selection Sort: %d comparações\n", comparacoesSelection);
                printf("\n💡 O algoritmo com MENOS comparações é o mais eficiente neste caso.\n");
                
                pausar();
                break;
            }
            
            case 0:
                printf("\nVoltando...\n");
                break;
                
            default:
                printf("\n❌ Opção inválida!\n");
                pausar();
        }
        
    } while (opcao != 0);
}

/**
 * Função: exibirMenuBusca
 * Descrição: Menu para buscar componentes
 */
void exibirMenuBusca() {
    if (totalComponentes == 0) {
        printf("\n❌ Nenhum componente cadastrado!\n");
        return;
    }
    
    int opcao;
    char nomeBusca[MAX_NOME];
    
    do {
        printf("\n🔍 SISTEMA DE BUSCA\n");
        printf("===================\n");
        printf("1. Busca Sequencial (sem ordenação)\n");
        printf("2. Busca Binária (requer ordenação por nome)\n");
        printf("0. Voltar\n");
        printf("===================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1: {
                // Busca sequencial
                printf("\n🔍 BUSCA SEQUENCIAL\n");
                printf("-------------------\n");
                printf("Digite o nome do componente: ");
                fgets(nomeBusca, MAX_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                
                int encontrado = 0;
                int comparacoes = 0;
                
                for (int i = 0; i < totalComponentes; i++) {
                    comparacoes++;
                    if (strcasecmp(componentes[i].nome, nomeBusca) == 0) {
                        printf("\n✅ Componente encontrado!\n");
                        printf("  Nome: %s\n", componentes[i].nome);
                        printf("  Tipo: %s\n", componentes[i].tipo);
                        printf("  Prioridade: %d\n", componentes[i].prioridade);
                        printf("📊 Comparações: %d\n", comparacoes);
                        encontrado = 1;
                        break;
                    }
                }
                
                if (!encontrado) {
                    printf("❌ Componente não encontrado!\n");
                    printf("📊 Comparações: %d\n", comparacoes);
                }
                
                pausar();
                break;
            }
            
            case 2: {
                // Busca binária
                printf("\n🔍 BUSCA BINÁRIA\n");
                printf("----------------\n");
                
                // Ordena uma cópia por nome
                Componente copia[MAX_COMPONENTES];
                copiarVetor(componentes, copia, totalComponentes);
                bubbleSortNome(copia, totalComponentes);
                
                printf("✅ Vetor ordenado por nome para a busca!\n\n");
                printf("Digite o nome do componente: ");
                fgets(nomeBusca, MAX_NOME, stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                
                int posicao = buscaBinariaPorNome(copia, totalComponentes, nomeBusca);
                
                if (posicao != -1) {
                    printf("\n📋 Detalhes do componente:\n");
                    printf("  Nome: %s\n", copia[posicao].nome);
                    printf("  Tipo: %s\n", copia[posicao].tipo);
                    printf("  Prioridade: %d\n", copia[posicao].prioridade);
                    printf("  Posição no vetor ordenado: %d\n", posicao + 1);
                }
                
                pausar();
                break;
            }
            
            case 0:
                printf("\nVoltando...\n");
                break;
                
            default:
                printf("\n❌ Opção inválida!\n");
                pausar();
        }
        
    } while (opcao != 0);
}

/**
 * Função: exibirMenuPrincipal
 * Descrição: Menu principal do sistema
 */
void exibirMenuPrincipal() {
    printf("\n🎮 SISTEMA DE MONTAGEM DA TORRE DE FUGA\n");
    printf("========================================\n");
    printf("📦 Componentes cadastrados: %d/%d\n", totalComponentes, MAX_COMPONENTES);
    printf("========================================\n");
    printf("1. Cadastrar componente\n");
    printf("2. Listar todos os componentes\n");
    printf("3. Algoritmos de ordenação\n");
    printf("4. Buscar componente\n");
    printf("5. Simular montagem da torre\n");
    printf("6. Exibir componentes-chave\n");
    printf("0. Sair do sistema\n");
    printf("========================================\n");
    printf("Escolha: ");
}

// ============================================
// FUNÇÃO PRINCIPAL
// ============================================

int main() {
    int opcao;
    
    printf("🎮 BEM-VINDO AO SISTEMA DE MONTAGEM DA TORRE DE FUGA\n");
    printf("====================================================\n");
    printf("🏗️ Monte a torre de resgate com os componentes certos!\n");
    printf("⚡ Cada componente tem uma prioridade para a fuga!\n\n");
    
    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                cadastrarComponente();
                pausar();
                break;
                
            case 2:
                listarComponentes(componentes, totalComponentes, 
                                 "📋 LISTA DE COMPONENTES CADASTRADOS");
                pausar();
                break;
                
            case 3:
                exibirMenuOrdenacao();
                break;
                
            case 4:
                exibirMenuBusca();
                break;
                
            case 5:
                simularMontagemTorre();
                pausar();
                break;
                
            case 6:
                exibirComponentesChave();
                pausar();
                break;
                
            case 0:
                printf("\n👋 Saindo do sistema...\n");
                printf("🏆 Você está pronto para escapar!\n");
                printf("Boa sorte na sua jornada!\n");
                break;
                
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
                pausar();
        }
        
    } while (opcao != 0);
    
    return 0;
}