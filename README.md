# AED2-ACH2024
Repositório contendo os códigos da disciplina Algoritmos e Estruturas de Dados 2, ministrado pela professora Ariane Machado Lima, na Escola de Artes, Ciências e Humanidades (EACH) da Universidade de São Paulo


Essa disciplina contou com dois exercícios programa, um implementando uma estrutura de **grafo por meio de lista de adjacência** e outro de manipulação de uma **árvore B+**.


## Conectividade em grafos não direcionados 

Implementado os seguintes algoritmos para grafos:

- [Busca em Largura](https://github.com/martinsjeniffer/AED2-ACH2024/blob/main/GRAFOS/EP1/buscaEmLargura.c)
- [Busca em profundidade](https://github.com/martinsjeniffer/AED2-ACH2024/blob/main/GRAFOS/EP1/buscaEmProfundidade.c)
- [Componentes Conectados](https://github.com/martinsjeniffer/AED2-ACH2024/blob/main/GRAFOS/EP1/componentesConexos.c)
- [Vértices de articulação](https://github.com/martinsjeniffer/AED2-ACH2024/blob/main/GRAFOS/EP1/README.md)

### Funcionamento

O algoritmo receberá as informações do grafo por meio de um arquivo chamado [`entrada.txt`](https://github.com/martinsjeniffer/AED2-ACH2024/blob/main/GRAFOS/EP1/testes/entrada1.txt).

- Para compilar e gerar os executáveis usando Makefile: 
    ```
      make
    ```

- Para limpar os executáveis do repositório: 
    ```
      make clean
    ```

- Para executar o programa: 
    ```
      ./conectividade.exe
    ```


## Árvores B+

Implementado os seguintes algoritmos para árvores B+:

- [Inserção de nó](https://github.com/martinsjeniffer/AED2-ACH2024/blob/main/MEM%C3%93RIA%20SECUND%C3%81RIA/EP2.c#L148)
- [Impressão com travessia **in-ordem**](https://github.com/martinsjeniffer/AED2-ACH2024/blob/main/MEM%C3%93RIA%20SECUND%C3%81RIA/EP2.c#L50)

### Funcionamento

- Para compilar e gerar os executáveis: 
    ```
      gcc EP2.c -o ep2
    ```


- Para executar o programa: 
    ```
      ./ep2.exe entrada.txt saida.txt
    ```
    
  Sendo [`entrada.txt`](https://github.com/martinsjeniffer/AED2-ACH2024/blob/main/MEM%C3%93RIA%20SECUND%C3%81RIA/entrada.txt) um arquivo contendo as instruções de manipulação da árvore B+.
  
