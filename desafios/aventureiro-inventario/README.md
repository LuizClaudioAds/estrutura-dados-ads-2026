# 🎮 Sistema de Inventário - Vetor vs Lista Encadeada

## 📋 Descrição do Projeto

Este sistema demonstra na prática as diferenças de desempenho entre duas estruturas de dados fundamentais: **Vetor (Lista Sequencial)** e **Lista Encadeada**. Desenvolvido em linguagem C, o projeto simula um sistema de inventário de um jogo de sobrevivência, onde o jogador precisa gerenciar itens rapidamente em situações de perigo.

## 🎯 Objetivo

Comparar empiricamente o comportamento de vetores e listas encadeadas nas operações básicas de gerenciamento de dados:
- Inserção de itens
- Remoção de itens
- Busca sequencial
- Busca binária (exclusiva para vetor)
- Ordenação

## 🚀 Funcionalidades

### Estruturas Implementadas

#### 1. **Vetor (Lista Sequencial)**
- Tamanho fixo (MAX_ITENS = 10)
- Acesso direto por índice
- Suporte a ordenação (Bubble Sort)
- **Busca Binária** (O(log n)) após ordenação
- Contador de comparações em buscas

#### 2. **Lista Encadeada**
- Tamanho dinâmico
- Inserção/Remoção no início O(1)
- Uso eficiente de memória
- Busca sequencial (O(n))
- Não suporta busca binária

### Operações Comuns
- ✅ Inserir novo item
- ✅ Listar todos os itens
- ✅ Buscar item por nome
- ✅ Remover item por nome

### Diferenciais
- 📊 **Contadores de comparações** em todas as buscas
- ⚡ **Busca binária** exclusiva para vetor
- 📈 **Comparação de desempenho** entre estruturas
- 🧹 Liberação automática de memória

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C (ISO C99)
- **Bibliotecas:**
  - `stdio.h` - Entrada/Saída
  - `stdlib.h` - Alocação dinâmica
  - `string.h` - Manipulação de strings
  - `time.h` - Medição de tempo (opcional)

## 📂 Estrutura do Código
├── Estruturas de Dados
│ ├── Item (nome, tipo, quantidade)
│ └── No (dados, *proximo)
│
├── Funções do Vetor
│ ├── inserirItemVetor()
│ ├── listarItensVetor()
│ ├── buscarSequencialVetor()
│ ├── buscarBinariaVetor()
│ ├── ordenarVetor()
│ └── removerItemVetor()
│
├── Funções da Lista Encadeada
│ ├── inserirItemLista()
│ ├── listarItensLista()
│ ├── buscarItemLista()
│ ├── removerItemLista()
│ └── liberarLista()
│
└── Interface
├── Menu Principal
├── Menu de Estruturas
└── Comparador de Desempenho


## 🔍 Comparativo de Desempenho

| Operação | Vetor | Lista Encadeada | Vencedor |
|----------|-------|-----------------|----------|
| **Busca Sequencial** | O(n) - Acesso direto | O(n) - Percorre ponteiros | ⚖️ Empate |
| **Busca Binária** | O(log n) ✅ | ❌ Não suporta | 🏆 Vetor |
| **Inserção (início)** | O(n) - Desloca elementos | O(1) - Ajusta ponteiros | 🏆 Lista |
| **Inserção (final)** | O(1) - Se houver espaço | O(n) - Percorre até o fim | 🏆 Vetor |
| **Remoção** | O(n) - Desloca elementos | O(1) - Ajusta ponteiros | 🏆 Lista |
| **Memória** | Fixa (pode desperdiçar) | Dinâmica (usa só o necessário) | 🏆 Lista |

## 💡 Insights para Jogos

### Quando usar VETOR
- ✅ Buscas frequentes de itens críticos
- ✅ Inventário com tamanho máximo definido
- ✅ Necessidade de ordenação e busca rápida (busca binária)
- ✅ Acesso aleatório por índice

### Quando usar LISTA ENCADEADA
- ✅ Muitas inserções e remoções dinâmicas
- ✅ Tamanho do inventário imprevisível
- ✅ Memória limitada (uso dinâmico)
- ✅ Inserção/remoção no início da lista