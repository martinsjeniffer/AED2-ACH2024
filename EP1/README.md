<style>
    * {
        font-family: "Times New Roman", Times, serif;
    }
    h1, h2, h3 {
        text-align: center;
    }
</style>

### ACH2024 - Algoritmos e Estrutura de Dados II
### Jeniffer Florinda Martins da Silva, nusp **10377966**

<hr>

### VÉRTICES DE ARTICULAÇÃO

Um vértice é dito vértice de articulação se ele é um vértice que, se retirado do grafo, o separaria em pelo menos dois subgrafos disjuntos.

Conseguimos determinar isso observando a Árvore de Busca em Profundidade, uma vez que, na Árvore BP, um vértice é um ponto de articulação se uma das condições abaixo forem verdadeiras:

1. `u` é a raiz da árvore BP e tem pelo menos **dois** filhos.
2. `u` não é a raiz da árvore BP e tem um adjacente `v` que nenhum vértice no subgrafo com raiz em `v` tem uma aresta de retorno para um dos antecessores de `u` 

Para verificar as condições temos o vetor `antecessor[]`, que armazena o pai de cada vértice `u`, o `cor[]` que marca se o vértice já foi visitado pelo esquema de cores descrito em aula (branco, cinza e preto), `tempoDescobrimento[]` que armazena o tempo de descoberta (momento em que vira cinza) de cada vértice e `exploracaoBP[]` que terá o menor valor de `tempoDescobrimento` acessível por uma aresta de retorno na árvore de busca de profundidade.

No caso da condição 1, contamos os filhos do vértice, se ele for a raiz da árvore (ou seja, se não tivermos `antecessor[vertice]`) ele é um vértice de articulação.

Para a condição 2 precisamos avaliar o `exploracaoBP[]` e fazer duas verificações:

- Se a subarvore com raiz em `v` tem alguma conexão com um dos antecessores de `u`

- Se `(u, v)` é uma aresta de retorno
