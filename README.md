# Impacto da Memória Cache no Desempenho de Software

**Disciplina:** Arquitetura e Organização de Computadores  
**Autores:** Carlos Eduardo Felix Ramos, José Pedro de Lira Barbosa, Cleverson Alves de Almeida  
**Professora:** Nathalia Alves

---

## Sobre o Experimento

Este projeto demonstra como o padrão de acesso à memória afeta o desempenho de programas em C.  
Duas funções percorrem a mesma matriz bidimensional de duas formas:

- **por_linha** — itera linha por linha (*row-major*), acesso sequencial, stride de 4 bytes.  
- **por_coluna** — itera coluna por coluna (*column-major*), stride de `N × 4` bytes.

A diferença de desempenho ilustra diretamente o princípio da **localidade espacial** e o impacto dos *cache misses* no hardware real.

---

## Resultados

| N     | Tamanho | Tempo — linha (s) | Tempo — coluna (s) | Razão  |
|-------|---------|-------------------|--------------------|--------|
| 512   | 1 MB    | 0,000415          | 0,000385           | 0,93×  |
| 1024  | 4 MB    | 0,001720          | 0,001740           | 1,01×  |
| 2048  | 16 MB   | 0,007000          | 0,012900           | 1,84×  |
| 4096  | 64 MB   | 0,028000          | 0,083000           | **2,96×** |

Para N = 4.096 (matriz de 64 MB, acima da capacidade das caches L2/L3), o acesso por coluna foi **~3× mais lento**.

---

## Como Compilar e Executar

**Pré-requisito:** GCC instalado (testado com GCC 14 via [MSYS2 UCRT64](https://www.msys2.org) no Windows 11).

```bash
# Compilar com otimizações desabilitadas (essencial para o experimento)
gcc -O0 -o main main.c

# Executar
./main
```

> **Por que `-O0`?** Com `-O2`/`-O3` o compilador pode reorganizar os loops e eliminar a diferença de desempenho que o experimento busca evidenciar.

**Saída esperada:**

```
N      | Linha (s)    | Coluna (s)   | Razao
-------|--------------|--------------|----------
512    | 0.000415     | 0.000385     | 0.93
1024   | 0.001720     | 0.001740     | 1.01
2048   | 0.007000     | 0.012900     | 1.84
4096   | 0.028000     | 0.083000     | 2.96
```

---

## Estrutura do Repositório

```
cache-experimento/
├── main.c          # Código-fonte do experimento
├── main.exe        # Executável pré-compilado (Windows 64-bit)
└── README.md
```

---

## Conceitos Envolvidos

- **Hierarquia de memória:** registradores → cache L1/L2/L3 → RAM. Um acesso à RAM é ~100× mais lento que um acerto de cache L1.
- **Cache line:** bloco de 64 bytes carregado por vez. O acesso por linha usa todos os 16 `int`s da linha; o acesso por coluna usa apenas 1 e descarta os 15 restantes.
- **Localidade espacial:** programas que acessam endereços vizinhos em sequência exploram o pré-carregamento da cache e alcançam alto desempenho.

---

## Referências

- STALLINGS, William. *Arquitetura e Organização de Computadores*. 10. ed. Pearson, 2018.  
- PATTERSON, David A.; HENNESSY, John L. *Organização e Projeto de Computadores*. 5. ed. Elsevier, 2017.  
- Free Software Foundation. *GCC, the GNU Compiler Collection*. https://gcc.gnu.org  
- MSYS2 Development Team. *MSYS2*. https://www.msys2.org
