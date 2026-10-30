#ifndef CATEGORIA_H
#define CATEGORIA_H

#define MAX_CATEGORIAS 20
#define ARQ_CATEGORIAS "categorias.txt"

struct Categoria {
    int codigo;
    char nome[30];
};

/* Busca pelo codigo. Devolve a posicao na lista ou -1 */
int buscarCategoriaPorCodigo(struct Categoria lista[], int total, int codigo);

void mostrarCategorias(struct Categoria lista[], int total);
void listarCategorias(struct Categoria lista[], int total);

/* Cadastra uma categoria e devolve o novo total */
int cadastrarCategoria(struct Categoria lista[], int total);

/* Submenu de categorias. Devolve o total atualizado */
int menuCategorias(struct Categoria lista[], int total);

/* Arquivo: codigo;nome (uma categoria por linha) */
void salvarCategorias(struct Categoria lista[], int total);
int carregarCategorias(struct Categoria lista[]);

#endif
