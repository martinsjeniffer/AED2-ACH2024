void GenericoAGM() {
  S = Ø;
  while (S não consititui uma árvore geradora mínima) {
    (u,v) = seleciona(A);
    if (aresta (u,v) é segura para S) 
      S = S + {(u,v)}
  }
  return S;
}

void PrimAGM(grafo, pesos, raiz) {
/* INICIALIZAÇÃO */
    para cada vértice u do grafo {
        key[u] = +INFINITO;
        antecessor[u] = NULL; 
    }
    key[raiz] = 0; //coloca ele direto na AGM
    FilaPrioridade = {todos os vertices, incluindo a raiz};
/* INICIALIZAÇÃO */

    while (FilaPrioridade != Ø) {
        u = tiraPrimeiroFilaPrioridade(FilaPrioridade);
        para cada vertice v ADJACENTE de u {
            if (v está na FilaPrioridade e pesos(u,v) < key[v]) {
                antecessor[v] = u;
                key[v] = pesos(u,v);
            }
        }
    }
}

void KruskalAGM(grafo, pesos) {
    Arestas = Ø;
    para cada vertice v do grafo {
        ConjuntoDisjunto(v); 
    }

    ordena todas as arestas do grafo por ordem não-decrescente de peso; // O(A log A)

    para cada aresta (u,v) do grafo, percorrido pela ordem não-decrescente de peso {
        if (raizDoConjuntoDoElemento(u) != raizDoConjuntoDoElemento(v)) {
            Acrescenta o {(u,v)} no conjunto Arestas
            UneConjuntos(u,v);
        }
    }

    return Arestas;
}

// conjunto com só um elemento
// MAKE-SET
void ConjuntoDisjunto(elemento) {
    pai[elemento] = elemento;
    // limitante superior da altura de x
    // (comprimento do caminho entre x e a folha descendente mais distante)
    rank[elemento] = 0;
}

// UNION
void UneConjuntos(x, y) {
    Link(raizDoConjuntoDoElemento(x), raizDoConjuntoDoElemento(y))
}

// u, v tem que ser as raizes dessas duas arvores
// Procura nao deixar a arvore mais alta do que poderia
// para otimizar a funcao raizDoConjuntoDoElemento()
void Link(x,y) {
    if (rank[x] > rank[y]) {
        pai[y] = x;
    }
    else {
        pai[x] = y;
        if (rank[x] == rank[y]) {
            rank[y] = rank[y] + 1;
        }
    }
}

// FIND-SET VERSÃO 01
void raizDoConjuntoDoElemento(x) {
    if (x != pai[x]) return raizDoConjuntoDoElemento(pai[x]);

    return x;
}

// FIND-SET VERSÃO 02
void raizDoConjuntoDoElemento(x) {
    if (x != pai[x]) {
        pai[x] = raizDoConjuntoDoElemento(pai[x]);
    }

    return pai[x];
}