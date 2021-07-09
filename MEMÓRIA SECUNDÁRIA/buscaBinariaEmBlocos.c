buscaBinaria(k)
{
    inf ← primeiro_bloco;
    sup ← primeiro_bloco + b - 1;
    enquanto(inf <= sup)
    {
        m ← floor((inf + sup) / 2);
        lê bloco m do disco para o buffer

        se(k < chave do primeiro registro do bloco m)
            sup ← m – 1;
        senão se(k > chave do último registro do bloco m)
            inf ← m + 1;
        senão se(k = chave de algum registro do bloco m)
            retorna TRUE
        senão 
            retorna FALSE
    }
}