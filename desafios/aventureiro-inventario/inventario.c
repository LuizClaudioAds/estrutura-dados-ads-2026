#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// ============================================
// ESTRUTURAS DE DADOS
// ============================================

// Estrutura base do Item (compartilhada entre vetor e lista)
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// Estrutura do Nó para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ============================================
// VARIÁVEIS GLOBAIS - VETOR
// ============================================
Item inventarioVetor[MAX_ITENS];
int totalItensVetor = 0;

// ============================================
// VARIÁVEIS GLOBAIS - LISTA ENCADEADA
// ============================================
No* cabecaLista = NULL;  // Ponteiro para o primeiro nó
int totalItensLista = 0;

// ============================================
// CONTADORES DE COMPARAÇÕES
// ============================================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ============================================
// PROTÓTIPOS DAS FUNÇÕES - VETOR
// ============================================
void inserirItemVetor();
void listarItensVetor();
void buscarSequencialVetor();
void buscarBinariaVetor();
void ordenarVetor();
void removerItemVetor();

// ============================================
// PROTÓTIPOS DAS FUNÇÕES - LISTA ENCADEADA
// ============================================
void inserirItemLista();
void listarItensLista();
void buscarItemLista();
void removerItemLista();
void liberarLista();

// ============================================
// PROTÓTIPOS - MENU E UTILITÁRIOS
// ============================================
void exibirMenuPrincipal();
void exibirMenuEstrutura();
void limparBuffer();
void pausar();

// ============================================
// IMPLEMENTAÇÃO - FUNÇÕES DO VETOR
// ============================================

/**
 * Função: inserirItemVetor
 * Descrição: Insere um novo item no vetor (lista sequencial)
 * Complexidade: O(1) - inserção no final
 * Diferença da lista: Vetor tem tamanho fixo, lista é dinâmica
 */
void inserirItemVetor() {
    if (totalItensVetor >= MAX_ITENS) {
        printf("\n❌ Mochila VETOR cheia! Capacidade máxima de %d itens.\n", MAX_ITENS);
        return;
    }
    
    printf("\n📦 CADASTRO NO VETOR\n");
    printf("--------------------\n");
    
    limparBuffer();
    
    printf("Nome do item: ");
    fgets(inventarioVetor[totalItensVetor].nome, MAX_NOME, stdin);
    inventarioVetor[totalItensVetor].nome[strcspn(inventarioVetor[totalItensVetor].nome, "\n")] = '\0';
    
    printf("Tipo (arma/municao/cura/ferramenta): ");
    fgets(inventarioVetor[totalItensVetor].tipo, MAX_TIPO, stdin);
    inventarioVetor[totalItensVetor].tipo[strcspn(inventarioVetor[totalItensVetor].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &inventarioVetor[totalItensVetor].quantidade);
    
    totalItensVetor++;
    printf("\n✅ Item inserido no VETOR com sucesso!\n");
}

/**
 * Função: listarItensVetor
 * Descrição: Lista todos os itens do vetor
 * Complexidade: O(n) - percorre todo o vetor
 * Diferença da lista: Acesso direto por índice é mais rápido
 */
void listarItensVetor() {
    printf("\n🎒 INVENTÁRIO - VETOR (%d/%d itens)\n", totalItensVetor, MAX_ITENS);
    printf("=====================================\n");
    
    if (totalItensVetor == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    
    for (int i = 0; i < totalItensVetor; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("  Nome: %s\n", inventarioVetor[i].nome);
        printf("  Tipo: %s\n", inventarioVetor[i].tipo);
        printf("  Quantidade: %d\n", inventarioVetor[i].quantidade);
    }
}

/**
 * Função: buscarSequencialVetor
 * Descrição: Busca item por nome usando busca sequencial
 * Complexidade: O(n) no pior caso
 * Contador: Incrementa comparacoesSequencial a cada comparação
 * Diferença da lista: Vetor tem acesso direto, lista percorre ponteiros
 */
void buscarSequencialVetor() {
    char nomeBusca[MAX_NOME];
    int encontrado = 0;
    comparacoesSequencial = 0;  // Zera o contador
    
    if (totalItensVetor == 0) {
        printf("\n❌ Mochila vazia!\n");
        return;
    }
    
    printf("\n🔍 BUSCA SEQUENCIAL - VETOR\n");
    printf("---------------------------\n");
    
    limparBuffer();
    printf("Digite o nome do item: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca sequencial com contador
    for (int i = 0; i < totalItensVetor; i++) {
        comparacoesSequencial++;  // Conta cada comparação
        if (strcasecmp(inventarioVetor[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("  Nome: %s\n", inventarioVetor[i].nome);
            printf("  Tipo: %s\n", inventarioVetor[i].tipo);
            printf("  Quantidade: %d\n", inventarioVetor[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\n❌ Item não encontrado.\n");
    }
    
    printf("\n📊 Comparações realizadas: %d\n", comparacoesSequencial);
}

/**
 * Função: ordenarVetor
 * Descrição: Ordena o vetor por nome usando Bubble Sort
 * Complexidade: O(n²) no pior caso
 * Importância: Ordenação é pré-requisito para busca binária
 * Diferença da lista: Ordenar lista encadeada é mais complexo (requer troca de ponteiros)
 */
void ordenarVetor() {
    if (totalItensVetor <= 1) {
        printf("\nℹ️ Vetor já está ordenado ou vazio.\n");
        return;
    }
    
    printf("\n🔄 ORDENANDO VETOR (Bubble Sort)...\n");
    
    Item temp;
    int trocas = 0;
    
    for (int i = 0; i < totalItensVetor - 1; i++) {
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcasecmp(inventarioVetor[j].nome, inventarioVetor[j + 1].nome) > 0) {
                // Troca os itens
                temp = inventarioVetor[j];
                inventarioVetor[j] = inventarioVetor[j + 1];
                inventarioVetor[j + 1] = temp;
                trocas++;
            }
        }
    }
    
    printf("✅ Vetor ordenado! (%d trocas realizadas)\n", trocas);
}

/**
 * Função: buscarBinariaVetor
 * Descrição: Busca item usando busca binária (requer vetor ordenado)
 * Complexidade: O(log n)
 * Contador: Incrementa comparacoesBinaria a cada comparação
 * Vantagem sobre sequencial: MUITO mais rápido em vetores grandes
 * Diferença da lista: Busca binária NÃO funciona em lista encadeada
 */
void buscarBinariaVetor() {
    char nomeBusca[MAX_NOME];
    int encontrado = 0;
    comparacoesBinaria = 0;
    
    if (totalItensVetor == 0) {
        printf("\n❌ Mochila vazia!\n");
        return;
    }
    
    // Verifica se o vetor está ordenado
    int estaOrdenado = 1;
    for (int i = 0; i < totalItensVetor - 1; i++) {
        if (strcasecmp(inventarioVetor[i].nome, inventarioVetor[i + 1].nome) > 0) {
            estaOrdenado = 0;
            break;
        }
    }
    
    if (!estaOrdenado) {
        printf("\n⚠️ Vetor não está ordenado! Execute a ordenação primeiro.\n");
        return;
    }
    
    printf("\n🔍 BUSCA BINÁRIA - VETOR (REQUER ORDENAÇÃO)\n");
    printf("--------------------------------------------\n");
    
    limparBuffer();
    printf("Digite o nome do item: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca binária com contador
    int esquerda = 0;
    int direita = totalItensVetor - 1;
    int meio;
    
    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;
        comparacoesBinaria++;
        
        int comparacao = strcasecmp(inventarioVetor[meio].nome, nomeBusca);
        
        if (comparacao == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("  Nome: %s\n", inventarioVetor[meio].nome);
            printf("  Tipo: %s\n", inventarioVetor[meio].tipo);
            printf("  Quantidade: %d\n", inventarioVetor[meio].quantidade);
            encontrado = 1;
            break;
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    if (!encontrado) {
        printf("\n❌ Item não encontrado.\n");
    }
    
    printf("\n📊 Comparações realizadas: %d\n", comparacoesBinaria);
}

/**
 * Função: removerItemVetor
 * Descrição: Remove item do vetor por nome
 * Complexidade: O(n) - desloca elementos para preencher espaço
 * Diferença da lista: Vetor precisa deslocar, lista apenas ajusta ponteiros O(1)
 */
void removerItemVetor() {
    char nomeRemover[MAX_NOME];
    int encontrado = 0;
    
    if (totalItensVetor == 0) {
        printf("\n❌ Mochila vazia!\n");
        return;
    }
    
    printf("\n🗑️ REMOVER - VETOR\n");
    printf("------------------\n");
    
    limparBuffer();
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, MAX_NOME, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';
    
    for (int i = 0; i < totalItensVetor; i++) {
        if (strcasecmp(inventarioVetor[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            
            // Desloca todos os elementos seguintes uma posição para trás
            for (int j = i; j < totalItensVetor - 1; j++) {
                inventarioVetor[j] = inventarioVetor[j + 1];
            }
            
            totalItensVetor--;
            printf("\n✅ Item removido do VETOR com sucesso!\n");
            break;
        }
    }
    
    if (!encontrado) {
        printf("\n❌ Item não encontrado.\n");
    }
}

// ============================================
// IMPLEMENTAÇÃO - FUNÇÕES DA LISTA ENCADEADA
// ============================================

/**
 * Função: inserirItemLista
 * Descrição: Insere novo item no início da lista encadeada
 * Complexidade: O(1) - inserção no início
 * Vantagem sobre vetor: Não tem tamanho máximo fixo
 * Desvantagem: Maior uso de memória (cada nó tem ponteiro)
 */
void inserirItemLista() {
    printf("\n📦 CADASTRO NA LISTA ENCADEADA\n");
    printf("-------------------------------\n");
    
    // Aloca memória para o novo nó
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("\n❌ Erro ao alocar memória!\n");
        return;
    }
    
    limparBuffer();
    
    printf("Nome do item: ");
    fgets(novoNo->dados.nome, MAX_NOME, stdin);
    novoNo->dados.nome[strcspn(novoNo->dados.nome, "\n")] = '\0';
    
    printf("Tipo (arma/municao/cura/ferramenta): ");
    fgets(novoNo->dados.tipo, MAX_TIPO, stdin);
    novoNo->dados.tipo[strcspn(novoNo->dados.tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    
    // Insere no início da lista
    novoNo->proximo = cabecaLista;
    cabecaLista = novoNo;
    totalItensLista++;
    
    printf("\n✅ Item inserido na LISTA ENCADEADA com sucesso!\n");
}

/**
 * Função: listarItensLista
 * Descrição: Percorre a lista encadeada exibindo todos os itens
 * Complexidade: O(n) - percorre todos os nós
 * Diferença do vetor: Acesso sequencial através de ponteiros, sem índice
 */
void listarItensLista() {
    printf("\n🎒 INVENTÁRIO - LISTA ENCADEADA (%d itens)\n", totalItensLista);
    printf("===========================================\n");
    
    if (cabecaLista == NULL) {
        printf("Mochila vazia!\n");
        return;
    }
    
    No* atual = cabecaLista;
    int contador = 1;
    
    while (atual != NULL) {
        printf("\nItem %d:\n", contador);
        printf("  Nome: %s\n", atual->dados.nome);
        printf("  Tipo: %s\n", atual->dados.tipo);
        printf("  Quantidade: %d\n", atual->dados.quantidade);
        atual = atual->proximo;
        contador++;
    }
}

/**
 * Função: buscarItemLista
 * Descrição: Busca item na lista encadeada por nome (busca sequencial)
 * Complexidade: O(n) no pior caso
 * Diferença do vetor: Cada acesso requer percorrer ponteiros
 * Desvantagem: Não é possível busca binária em lista encadeada
 */
void buscarItemLista() {
    char nomeBusca[MAX_NOME];
    int encontrado = 0;
    comparacoesSequencial = 0;
    
    if (cabecaLista == NULL) {
        printf("\n❌ Mochila vazia!\n");
        return;
    }
    
    printf("\n🔍 BUSCA - LISTA ENCADEADA\n");
    printf("--------------------------\n");
    
    limparBuffer();
    printf("Digite o nome do item: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    No* atual = cabecaLista;
    
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcasecmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("  Nome: %s\n", atual->dados.nome);
            printf("  Tipo: %s\n", atual->dados.tipo);
            printf("  Quantidade: %d\n", atual->dados.quantidade);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }
    
    if (!encontrado) {
        printf("\n❌ Item não encontrado.\n");
    }
    
    printf("\n📊 Comparações realizadas: %d\n", comparacoesSequencial);
}

/**
 * Função: removerItemLista
 * Descrição: Remove item da lista encadeada por nome
 * Complexidade: O(n) - precisa encontrar o nó
 * Vantagem sobre vetor: Não precisa deslocar elementos, apenas ajustar ponteiros
 * Desvantagem: Não tem acesso aleatório
 */
void removerItemLista() {
    char nomeRemover[MAX_NOME];
    int encontrado = 0;
    
    if (cabecaLista == NULL) {
        printf("\n❌ Mochila vazia!\n");
        return;
    }
    
    printf("\n🗑️ REMOVER - LISTA ENCADEADA\n");
    printf("----------------------------\n");
    
    limparBuffer();
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, MAX_NOME, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';
    
    No* atual = cabecaLista;
    No* anterior = NULL;
    
    // Caso especial: remover o primeiro nó
    if (strcasecmp(cabecaLista->dados.nome, nomeRemover) == 0) {
        cabecaLista = cabecaLista->proximo;
        free(atual);
        totalItensLista--;
        printf("\n✅ Item removido da LISTA com sucesso!\n");
        return;
    }
    
    // Busca o nó a ser removido
    while (atual != NULL && strcasecmp(atual->dados.nome, nomeRemover) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (atual == NULL) {
        printf("\n❌ Item não encontrado.\n");
        return;
    }
    
    // Remove o nó (ajusta o ponteiro do anterior)
    anterior->proximo = atual->proximo;
    free(atual);
    totalItensLista--;
    
    printf("\n✅ Item removido da LISTA com sucesso!\n");
}

/**
 * Função: liberarLista
 * Descrição: Libera toda a memória alocada para a lista encadeada
 * Importante: Evita vazamento de memória
 */
void liberarLista() {
    No* atual = cabecaLista;
    No* prox;
    
    while (atual != NULL) {
        prox = atual->proximo;
        free(atual);
        atual = prox;
    }
    
    cabecaLista = NULL;
    totalItensLista = 0;
}

// ============================================
// FUNÇÕES UTILITÁRIAS
// ============================================

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

/**
 * Função: exibirMenuEstrutura
 * Descrição: Exibe o menu de seleção de estrutura de dados
 */
void exibirMenuEstrutura() {
    int opcao;
    
    do {
        printf("\n🎮 ESCOLHA A ESTRUTURA DE DADOS\n");
        printf("================================\n");
        printf("1. Vetor (Lista Sequencial)\n");
        printf("2. Lista Encadeada\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("================================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                exibirMenuVetor();
                break;
            case 2:
                exibirMenuLista();
                break;
            case 0:
                printf("\nVoltando...\n");
                break;
            default:
                printf("\n❌ Opção inválida!\n");
        }
        
        if (opcao != 0) {
            pausar();
        }
        
    } while (opcao != 0);
}

/**
 * Função: exibirMenuVetor
 * Descrição: Menu de operações específicas do vetor
 */
void exibirMenuVetor() {
    int opcao;
    
    do {
        printf("\n📊 OPERAÇÕES COM VETOR\n");
        printf("=======================\n");
        printf("1. Inserir item\n");
        printf("2. Listar itens\n");
        printf("3. Buscar (Sequencial)\n");
        printf("4. Buscar (Binária) ⚡\n");
        printf("5. Ordenar vetor\n");
        printf("6. Remover item\n");
        printf("0. Voltar\n");
        printf("=======================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1: inserirItemVetor(); break;
            case 2: listarItensVetor(); break;
            case 3: buscarSequencialVetor(); break;
            case 4: buscarBinariaVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: removerItemVetor(); break;
            case 0: printf("\nVoltando...\n"); break;
            default: printf("\n❌ Opção inválida!\n");
        }
        
        if (opcao != 0) {
            pausar();
        }
        
    } while (opcao != 0);
}

/**
 * Função: exibirMenuLista
 * Descrição: Menu de operações específicas da lista encadeada
 */
void exibirMenuLista() {
    int opcao;
    
    do {
        printf("\n🔗 OPERAÇÕES COM LISTA ENCADEADA\n");
        printf("==================================\n");
        printf("1. Inserir item\n");
        printf("2. Listar itens\n");
        printf("3. Buscar item\n");
        printf("4. Remover item\n");
        printf("0. Voltar\n");
        printf("==================================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1: inserirItemLista(); break;
            case 2: listarItensLista(); break;
            case 3: buscarItemLista(); break;
            case 4: removerItemLista(); break;
            case 0: printf("\nVoltando...\n"); break;
            default: printf("\n❌ Opção inválida!\n");
        }
        
        if (opcao != 0) {
            pausar();
        }
        
    } while (opcao != 0);
}

/**
 * Função: exibirMenuPrincipal
 * Descrição: Menu principal do sistema
 */
void exibirMenuPrincipal() {
    printf("\n🎮 SISTEMA DE INVENTÁRIO - SOBREVIVÊNCIA\n");
    printf("========================================\n");
    printf("1. Gerenciar Mochila (Escolher Estrutura)\n");
    printf("2. Comparar Desempenho das Estruturas\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha: ");
}

/**
 * Função: compararEstruturas
 * Descrição: Demonstra a diferença de desempenho entre vetor e lista
 * Útil para entender na prática as diferenças das estruturas
 */
void compararEstruturas() {
    printf("\n📊 COMPARAÇÃO DE DESEMPENHO\n");
    printf("===========================\n");
    printf("\n🔍 BUSCA SEQUENCIAL:\n");
    printf("  - Vetor: O(n) - Acesso direto por índice\n");
    printf("  - Lista: O(n) - Percorre ponteiros (mais lento)\n");
    printf("\n🔍 BUSCA BINÁRIA (APENAS VETOR):\n");
    printf("  - Vetor: O(log n) - MUITO mais rápido para grandes volumes\n");
    printf("  - Lista: ❌ Não é possível - não tem acesso aleatório\n");
    printf("\n➕ INSERÇÃO:\n");
    printf("  - Vetor: O(1) no final, O(n) no início/meio\n");
    printf("  - Lista: O(1) no início, O(n) no final\n");
    printf("\n➖ REMOÇÃO:\n");
    printf("  - Vetor: O(n) - precisa deslocar elementos\n");
    printf("  - Lista: O(1) após encontrar o nó\n");
    printf("\n💾 MEMÓRIA:\n");
    printf("  - Vetor: Fixa, desperdício se não usada toda\n");
    printf("  - Lista: Dinâmica, usa exatamente o necessário\n");
    printf("\n✅ CONCLUSÃO:\n");
    printf("  - Para buscas frequentes: VETOR (com ordenação e busca binária)\n");
    printf("  - Para inserções/remoções frequentes: LISTA ENCADEADA\n");
    printf("  - Para jogos com itens críticos: VETOR com busca binária ⚡\n");
}

// ============================================
// FUNÇÃO PRINCIPAL
// ============================================

int main() {
    int opcao;
    
    printf("🎮 BEM-VINDO AO SISTEMA DE INVENTÁRIO\n");
    printf("====================================\n");
    printf("Compare o desempenho entre VETOR e LISTA ENCADEADA!\n\n");
    
    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao) {
            case 1:
                exibirMenuEstrutura();
                break;
            case 2:
                compararEstruturas();
                pausar();
                break;
            case 0:
                printf("\n👋 Saindo do sistema...\n");
                printf("Liberando memória da lista...\n");
                liberarLista();
                printf("Boa sorte na sua jornada de sobrevivência!\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
                pausar();
        }
        
    } while (opcao != 0);
    
    return 0;
}