#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

// Definição da struct Item
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// Variável global para o inventário
Item inventario[MAX_ITENS];
int totalItens = 0; //Contador de itens cadastrados

// Protótipo de Funções
void inserirItem();
void listarItens();
void buscarItem();
void removerItem();
void exibirMenu();

int main() {
    int opcao;
    
    printf("🎮 BEM-VINDO AO SISTEMA DE INVENTÁRIO\n");
    printf("====================================\n");
    printf("Sobreviva coletando e organizando seus recursos!\n\n");
    
    do {
        exibirMenu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                listarItens();
                break;
            case 3:
                buscarItem();
                break;
            case 4:
                removerItem();
                break;
            case 0:
                printf("\n👋 Saindo do sistema...\n");
                printf("Boa sorte na sua jornada de sobrevivência!\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }
        
        // Pausa para o usuário ver o resultado
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }
        
    } while (opcao != 0);
    
    return 0;
}

// Função para cadastrar um novo item no inventário
void inserirItem() {
    // Verifica se o inventário está cheio
    if (totalItens >= MAX_ITENS) {
        printf("\n❌ Mochila cheia! Capacidade máxima de %d itens.\n", MAX_ITENS);
        return;
    }
    
    printf("\n📦 CADASTRO DE ITEM\n");
    printf("-------------------\n");
    
    // Limpa o buffer do teclado
    getchar();
    
    // Lê o nome do item
    printf("Nome do item: ");
    fgets(inventario[totalItens].nome, MAX_NOME, stdin);
    // Remove o '\n' do final da string
    inventario[totalItens].nome[strcspn(inventario[totalItens].nome, "\n")] = '\0';
    
    // Lê o tipo do item
    printf("Tipo (arma/municao/cura/ferramenta): ");
    fgets(inventario[totalItens].tipo, MAX_TIPO, stdin);
    inventario[totalItens].tipo[strcspn(inventario[totalItens].tipo, "\n")] = '\0';
    
    // Lê a quantidade
    printf("Quantidade: ");
    scanf("%d", &inventario[totalItens].quantidade);
    
    // Incrementa o contador de itens
    totalItens++;
    
    printf("\n✅ Item cadastrado com sucesso!\n");
}

// Função para listar todos os itens do inventário
void listarItens() {
    printf("\n🎒 INVENTÁRIO DO JOGADOR\n");
    printf("==========================\n");
    
    if (totalItens == 0) {
        printf("Mochila vazia! Cadastre alguns itens primeiro.\n");
        return;
    }
    
    printf("📋 Itens cadastrados (%d/%d):\n\n", totalItens, MAX_ITENS);
    
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", inventario[i].nome);
        printf("  Tipo: %s\n", inventario[i].tipo);
        printf("  Quantidade: %d\n", inventario[i].quantidade);
        printf("  -------------------------\n");
    }
}

// Função para buscar um item pelo nome (busca sequencial)
void buscarItem() {
    char nomeBusca[MAX_NOME];
    int encontrado = 0;
    
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    printf("\n🔍 BUSCAR ITEM\n");
    printf("--------------\n");
    
    // Limpa o buffer
    getchar();
    
    printf("Digite o nome do item: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca sequencial
    for (int i = 0; i < totalItens; i++) {
        // Comparação case-insensitive (opcional)
        if (strcasecmp(inventario[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("  Nome: %s\n", inventario[i].nome);
            printf("  Tipo: %s\n", inventario[i].tipo);
            printf("  Quantidade: %d\n", inventario[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}
// Função para remover um item pelo nome
void removerItem() {
    char nomeRemover[MAX_NOME];
    int encontrado = 0;
    
    if (totalItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    printf("\n🗑️ REMOVER ITEM\n");
    printf("---------------\n");
    
    // Limpa o buffer
    getchar();
    
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, MAX_NOME, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';
    
    // Busca o item
    for (int i = 0; i < totalItens; i++) {
        if (strcasecmp(inventario[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            
            // Desloca os itens seguintes uma posição para trás
            for (int j = i; j < totalItens - 1; j++) {
                inventario[j] = inventario[j + 1];
            }
            
            totalItens--;
            printf("\n✅ Item '%s' removido com sucesso!\n", nomeRemover);
            break;
        }
    }
    
    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeRemover);
    }
}

// Função para exibir o menu
void exibirMenu() {
    printf("\n🎮 SISTEMA DE INVENTÁRIO - SOBREVIVÊNCIA\n");
    printf("========================================\n");
    printf("1. Cadastrar item\n");
    printf("2. Listar itens\n");
    printf("3. Buscar item\n");
    printf("4. Remover item\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Escolha uma opção: ");
}

