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
