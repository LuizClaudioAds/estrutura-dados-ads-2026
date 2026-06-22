# 🏗️ Sistema de Montagem da Torre de Fuga

## 📋 Descrição do Projeto

Este sistema simula o momento decisivo de um jogo de sobrevivência, onde o jogador precisa montar uma torre de resgate utilizando componentes específicos. O programa implementa e compara **três algoritmos clássicos de ordenação** (Bubble Sort, Insertion Sort e Selection Sort) e uma **busca binária eficiente**, permitindo ao jogador escolher a melhor estratégia para organizar os componentes da torre.

## 🎯 Objetivos do Projeto

1. **Implementar** três algoritmos de ordenação diferentes
2. **Comparar** o desempenho de cada algoritmo (tempo e comparações)
3. **Aplicar** busca binária em vetor ordenado
4. **Analisar** a eficiência de diferentes estratégias de ordenação
5. **Simular** a montagem da torre com priorização de componentes

## 🚀 Funcionalidades

### Gerenciamento de Componentes
- ✅ Cadastro de até 20 componentes
- ✅ Campos: Nome, Tipo e Prioridade (1-10)
- ✅ Listagem formatada de todos os componentes
- ✅ Identificação de componentes-chave (prioridade ≥ 8)

### Algoritmos de Ordenação

| Algoritmo | Critério | Complexidade | Característica |
|-----------|----------|--------------|----------------|
| **Bubble Sort** | Nome (string) | O(n²) | Simples, mas ineficiente |
| **Insertion Sort** | Tipo (string) | O(n²) | Eficiente para dados parcialmente ordenados |
| **Selection Sort** | Prioridade (int) | O(n²) | Sempre faz o mesmo número de comparações |

### Busca
- 🔍 **Busca Sequencial**: Para vetores não ordenados
- 🔍 **Busca Binária**: Para vetores ordenados por nome (O(log n))

### Análise de Desempenho
- 📊 Contador de comparações para cada algoritmo
- ⏱️ Medição de tempo de execução (clock())
- 📈 Comparação simultânea dos três algoritmos

### Simulação
- 🏗️ Montagem da torre por ordem de prioridade
- 🎯 Estratégia: componentes mais críticos primeiro

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C
- **Bibliotecas:**
  - `stdio.h` - Entrada/Saída
  - `stdlib.h` - Funções utilitárias
  - `string.h` - Manipulação de strings
  - `time.h` - Medição de tempo (clock())

## 📂 Estrutura do Código
Sistema de Montagem da Torre
├── Estrutura de Dados
│ └── Componente (nome, tipo, prioridade)
│
├── Algoritmos de Ordenação
│ ├── bubbleSortNome()
│ ├── insertionSortTipo()
│ └── selectionSortPrioridade()
│
├── Busca
│ ├── Busca Sequencial
│ └── buscaBinariaPorNome()
│
├── Utilitários
│ ├── cadastrarComponente()
│ ├── listarComponentes()
│ ├── copiarVetor()
│ └── exibirComponentesChave()
│
├── Medição de Desempenho
│ └── medirTempo()
│
└── Interface
├── Menu Principal
├── Menu de Ordenação
└── Menu de Busca