# Impacto da Memória Cache no Desempenho de Software

**Disciplina:** Arquitetura e Organização de Computadores  
**Autores:** Carlos Eduardo Felix Ramos, José Pedro de Lira Barbosa, Cleverson Alves de Almeida  
**Professora:** Nathalia Alves

---

## Sobre o Experimento

Este projeto demonstra como o padrão de acesso à memória afeta o desempenho de programas em C.  
A matriz é alocada em um único bloco contínuo de `N × N` inteiros (`int *A = malloc(N*N*sizeof(int))`)
e acessada como `A[i * N + j]`, garantindo o armazenamento *row-major* real.
Antes de cada medição, cada função é executada uma vez sem medir (aquecimento).

Duas funções percorrem a mesma matriz de duas formas:

- **por_linha** — itera linha por linha (*row-major*), acesso sequencial, stride de 4 bytes.  
- **por_coluna** — itera coluna por coluna (*column-major*), stride de `N × 4` bytes.

A diferença de desempenho ilustra diretamente o princípio da **localidade espacial** e o impacto dos *cache misses* no hardware real.

---

## Resultados

Média de 3 execuções completas do programa:

| N     | Tamanho | Tempo — linha (s) | Tempo — coluna (s) | Razão     |
|-------|---------|-------------------|--------------------|-----------|
| 512   | 1 MB    | 0,000413          | 0,000442           | 1,07×     |
| 1.024 | 4 MB    | 0,001740          | 0,004067           | 2,34×     |
| 2.048 | 16 MB   | 0,007100          | 0,032700           | 4,61×     |
| 4.096 | 64 MB   | 0,028778          | 0,202889           | **7,05×** |

Para N = 4.096 (matriz de 64 MB), o acesso por coluna foi cerca de 7× mais lento (média de 3 execuções; entre 6,66× e 7,47×).

---

## Como Compilar e Executar

**Pré-requisito:** GCC instalado (testado com GCC 14 via [MSYS2 UCRT64](https://www.msys2.org) no Windows 11).  
Processador usado nos testes: [modelo da CPU]

### Terminal MSYS2 UCRT64

```bash
gcc -O0 -Wall -o main main.c
./main
```

### PowerShell

```powershell
$env:Path = "C:\msys64\ucrt64\bin;" + $env:Path
gcc -O0 -Wall -o main main.c
.\main.exe
```

> **Por que `-O0`?** Para manter os laços exatamente como foram escritos, sem reorganização pelo compilador.

---

## Exemplo de saída (os valores variam conforme o hardware)

```
N      | Linha (s)    | Coluna (s)   | Razao
-------|--------------|--------------|----------
512    | 0.000415     | 0.000450     | 1.08
1024   | 0.001720     | 0.004020     | 2.34
2048   | 0.007100     | 0.032700     | 4.61
4096   | 0.028778     | 0.202889     | 7.05
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

- **Hierarquia de memória:** registradores → cache L1/L2/L3 → RAM. Um acesso à RAM é consideravelmente mais lento que um acerto de cache L1.
- **Cache line:** bloco de 64 bytes carregado por vez. O acesso por linha usa todos os 16 `int`s da linha; o acesso por coluna usa apenas 1 e descarta os 15 restantes.
- **Localidade espacial:** programas que acessam endereços vizinhos em sequência exploram o pré-carregamento da cache e alcançam alto desempenho.

---

## Referências

- STALLINGS, William. *Arquitetura e Organização de Computadores*. 10. ed. Pearson, 2018.  
- PATTERSON, David A.; HENNESSY, John L. *Organização e Projeto de Computadores*. [ano] ed. Elsevier.  
- Free Software Foundation. *GCC, the GNU Compiler Collection*. https://gcc.gnu.org  
- MSYS2 Development Team. *MSYS2*. https://www.msys2.org
