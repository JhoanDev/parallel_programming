# Programação Concorrente e Distribuída (PCD) 🧵🖥️

Este repositório contém a resolução das questões propostas na lista da disciplina de **Programação Concorrente e Distribuída**, organizada por unidades. A lista completa está disponível no arquivo [`lista.pdf`](./lista.pdf).

As questões abrangem conceitos fundamentais de concorrência, paralelismo, sincronização, semáforos, monitores, barreiras, comunicação entre processos, MPI, OpenMP, entre outros tópicos importantes da disciplina.

## Organização das pastas 📁

As resoluções estão divididas conforme a estrutura da lista:

### 📘 Unidade 1 – Conceitos Fundamentais de Concorrência
Contém explicações teóricas e exemplos em pseudocódigo para questões como:
- Condição de corrida
- Seção crítica
- Deadlock e starvation
- Primitivas de sincronização
- Exclusão mútua

### 📗 Unidade 2 – Sincronização e Programação Paralela com OpenMP
Contém resoluções com foco em:
- Semáforos
- Monitores
- Problema dos leitores e escritores
- Barreira de sincronização
- Implementações em C utilizando OpenMP

### 📙 Unidade 3 – Comunicação entre Processos com MPI
Abrange:
- Comunicação ponto-a-ponto
- Reduções, somas prefixadas e difusão
- Modelagem de desempenho
- Comunicação coletiva
- Implementações em C com MPI

## Arquivo da lista 📄
O arquivo [`lista.pdf`](./lista.pdf) contém todas as questões trabalhadas neste repositório.

## Estrutura de pastas resumida
```
.
├── lista.pdf
├── unidade_1/
├── unidade_2/
└── unidade_3/
```

## 💡 Observações
- Algumas questões possuem arquivos auxiliares como `.txt` de entrada/saída, `test.sh` para execução automatizada e variações de código (modificações, otimizações, etc.).
- Códigos foram escritos principalmente em C, com uso de OpenMP e MPI quando necessário.
- A organização busca manter uma correspondência direta com a numeração da lista original.

---

Sinta-se à vontade para explorar, testar os códigos e contribuir com melhorias!
