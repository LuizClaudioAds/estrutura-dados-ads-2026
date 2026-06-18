# 🎮 Desafio Novato - Sistema de Inventário

## 📋 Sobre o Desafio

Este é o primeiro desafio da disciplina de Estrutura de Dados, onde implementamos um sistema de inventário para um jogo de sobrevivência. O objetivo é praticar o uso de **structs** e **vetores** (listas sequenciais) em C.

## 🎯 Objetivos do Desafio

- ✅ Criar e manipular structs em C
- ✅ Utilizar vetores como estruturas de dados sequenciais
- ✅ Implementar operações básicas: inserção, remoção, busca e listagem
- ✅ Praticar modularização com funções
- ✅ Aplicar conceitos de jogos em programação

## 🕹️ Funcionalidades

### 1. Cadastrar Item
Permite adicionar um novo item ao inventário com:
- Nome (ex: "Faca", "Pistola", "Kit Médico")
- Tipo (arma, municao, cura, ferramenta)
- Quantidade

### 2. Listar Itens
Exibe todos os itens cadastrados com suas informações completas.

### 3. Buscar Item
Realiza uma busca sequencial por um item específico pelo nome.

### 4. Remover Item
Remove um item do inventário informando seu nome.

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C
- **Bibliotecas:** 
  - `stdio.h` - Entrada e saída
  - `string.h` - Manipulação de strings
  - `stdlib.h` - Funções utilitárias

## 📁 Estrutura do Código
inventario.c
├── Struct Item
│ ├── nome[30]
│ ├── tipo[20]
│ └── quantidade
├── Protótipo Funções
│ ├── inserirItem() - Cadastra novo item
│ ├── listarItens() - Mostra todos os itens
│ ├── buscarItem() - Busca item por nome
│ ├── removerItem() - Remove item do inventário
| └── exibirMenu()
└── main()
└── Menu interativo


## 🚀 Como Executar

### Compilação
```bash
gcc -o inventario inventario.c


### Executa
./inventario