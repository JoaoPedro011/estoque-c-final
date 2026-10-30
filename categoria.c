#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "util.h"

int buscarCategoriaPorCodigo(struct Categoria lista[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

/* Mostra so as linhas "codigo - nome" */
void mostrarCategorias(struct Categoria lista[], int total) {
    int i;
    for (i = 0; i < total; i++) {
        printf("  %d - %s\n", lista[i].codigo, lista[i].nome);
    }
}

void listarCategorias(struct Categoria lista[], int total) {
    printf("\n=== LISTA DE CATEGORIAS ===\n");
    if (total == 0) {
        printf("Nenhuma categoria foi cadastrada.\n");
        return;
    }
    mostrarCategorias(lista, total);
}

int cadastrarCategoria(struct Categoria lista[], int total) {
    struct Categoria nova;

    printf("\n=== CADASTRAR CATEGORIA ===\n");

    if (total >= MAX_CATEGORIAS) {
        printf("Lista cheia! Nao e possivel cadastrar mais categorias (maximo %d).\n", MAX_CATEGORIAS);
        return total;
    }

    /* Codigo: positivo (util) e nao repetido (depende da lista, entao fica aqui) */
    do {
        printf("Codigo da categoria: ");
        nova.codigo = lerInteiro(0);

        if (!inteiroPositivo(nova.codigo)) {
            printf("Codigo invalido! Digite um numero positivo.\n");
        } else if (buscarCategoriaPorCodigo(lista, total, nova.codigo) != -1) {
            printf("Ja existe uma categoria com esse codigo! Digite outro.\n");
            nova.codigo = 0;
        }
    } while (!inteiroPositivo(nova.codigo));

    /* Nome: nao pode ficar em branco (e sem ; para nao quebrar o arquivo) */
    do {
        printf("Nome da categoria: ");
        lerTexto(nova.nome, 30);

        if (!textoPreenchido(nova.nome)) {
            printf("O nome nao pode ficar em branco!\n");
        } else if (!textoSemCaractere(nova.nome, ';')) {
            printf("O nome nao pode ter ponto e virgula (;)!\n");
            nova.nome[0] = '\0';
        }
    } while (!textoPreenchido(nova.nome));

    lista[total] = nova;
    total = total + 1;

    printf("\n--- Categoria cadastrada com sucesso! ---\n");
    printf("Codigo: %d\n", nova.codigo);
    printf("Nome: %s\n", nova.nome);

    return total;
}

int menuCategorias(struct Categoria lista[], int total) {
    int opcao;

    do {
        printf("\n----- CATEGORIAS -----\n");
        printf("1 - Cadastrar Categoria\n");
        printf("2 - Listar Categorias\n");
        printf("3 - Voltar\n");
        printf("Escolha uma opcao: ");
        opcao = lerInteiro(0);

        switch (opcao) {
            case 1:
                total = cadastrarCategoria(lista, total);
                break;
            case 2:
                listarCategorias(lista, total);
                break;
            case 3:
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 3);

    return total;
}

void salvarCategorias(struct Categoria lista[], int total) {
    FILE *arq;
    int i;

    arq = fopen(ARQ_CATEGORIAS, "w");
    if (arq == NULL) {
        printf("Aviso: nao foi possivel salvar o arquivo %s\n", ARQ_CATEGORIAS);
        return;
    }
    for (i = 0; i < total; i++) {
        fprintf(arq, "%d;%s\n", lista[i].codigo, lista[i].nome);
    }
    fclose(arq);
}

/* Se o arquivo nao existir (primeira vez), devolve 0 e a lista comeca vazia */
int carregarCategorias(struct Categoria lista[]) {
    FILE *arq;
    char linha[100];
    int total = 0;

    arq = fopen(ARQ_CATEGORIAS, "r");
    if (arq == NULL) {
        return 0;
    }
    while (total < MAX_CATEGORIAS && fgets(linha, sizeof(linha), arq) != NULL) {
        if (sscanf(linha, "%d;%29[^\n]", &lista[total].codigo, lista[total].nome) == 2) {
            total++;
        }
    }
    fclose(arq);
    return total;
}
