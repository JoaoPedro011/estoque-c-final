#ifndef PRODUTO_H
#define PRODUTO_H

#include "categoria.h"

#define MAX_PRODUTOS 50
#define ARQ_PRODUTOS "produtos.txt"

struct Produto {
    int codigo;
    char nome[50];
    char prateleira;
    float preco;
    int quantidade;
    int disponivel;          /* sempre calculado a partir da quantidade */
    int categoria_codigo;    /* so o codigo; o nome vem da lista de categorias */
    int ativo;               /* 1 = normal, 0 = removido (exclusao logica) */
};

/* ----- buscas (devolvem a posicao na lista ou -1) ----- */
int buscarPorCodigo(struct Produto lista[], int total, int codigo);
int buscarAtivoPorCodigo(struct Produto lista[], int total, int codigo); /* ignora removidos */
int buscarPorNome(struct Produto lista[], int total, char nome[]);       /* ignora removidos */

/* ----- operacoes do menu ----- */
void exibirProduto(struct Produto p, struct Categoria cats[], int totalCats);
int cadastrarProduto(struct Produto lista[], int total, struct Categoria cats[], int totalCats);
void listarProdutos(struct Produto lista[], int total, struct Categoria cats[], int totalCats);
void pesquisarProduto(struct Produto lista[], int total, struct Categoria cats[], int totalCats);
void alterarEstoque(struct Produto lista[], int total, struct Categoria cats[], int totalCats);
void removerProduto(struct Produto lista[], int total);

/* ----- arquivo: codigo;nome;prateleira;preco;quantidade;disponivel;categoria;ativo ----- */
void salvarProdutos(struct Produto lista[], int total);
int carregarProdutos(struct Produto lista[]);

#endif
