#include <stdio.h>
#include "util.h"
#include "categoria.h"
#include "produto.h"

/* O main so mostra o menu, le a opcao e chama a funcao correspondente */

static void exibirMenu(void) {
    printf("\n===== SISTEMA DE ESTOQUE =====\n");
    printf("1 - Cadastrar Produto\n");
    printf("2 - Listar Produtos\n");
    printf("3 - Pesquisar Produto\n");
    printf("4 - Alterar Estoque de um Produto\n");
    printf("5 - Remover Produto\n");
    printf("6 - Categorias\n");
    printf("7 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    struct Produto produtos[MAX_PRODUTOS];
    struct Categoria categorias[MAX_CATEGORIAS];
    int totalProdutos;
    int totalCategorias;
    int opcao;

    /* Ao iniciar, carrega os dados dos arquivos (se existirem) */
    totalCategorias = carregarCategorias(categorias);
    totalProdutos = carregarProdutos(produtos);

    do {
        exibirMenu();
        opcao = lerInteiro(0);

        switch (opcao) {
            case 1:
                totalProdutos = cadastrarProduto(produtos, totalProdutos, categorias, totalCategorias);
                salvarProdutos(produtos, totalProdutos);
                break;
            case 2:
                listarProdutos(produtos, totalProdutos, categorias, totalCategorias);
                break;
            case 3:
                pesquisarProduto(produtos, totalProdutos, categorias, totalCategorias);
                break;
            case 4:
                alterarEstoque(produtos, totalProdutos, categorias, totalCategorias);
                salvarProdutos(produtos, totalProdutos);
                break;
            case 5:
                removerProduto(produtos, totalProdutos);
                salvarProdutos(produtos, totalProdutos);
                break;
            case 6:
                totalCategorias = menuCategorias(categorias, totalCategorias);
                salvarCategorias(categorias, totalCategorias);
                break;
            case 7:
                /* Ao sair, grava as duas listas de novo */
                salvarCategorias(categorias, totalCategorias);
                salvarProdutos(produtos, totalProdutos);
                printf("Dados salvos. Saindo do sistema... Ate mais!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
