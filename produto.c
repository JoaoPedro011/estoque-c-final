#include <stdio.h>
#include <string.h>
#include "produto.h"
#include "categoria.h"
#include "util.h"

/* ==================== REGRA DA DISPONIBILIDADE ==================== */

/* 1 se a quantidade for maior que zero, senao 0. Nunca e digitada pelo usuario */
static int calcularDisponibilidade(int quantidade) {
    if (quantidade > 0) {
        return 1;
    }
    return 0;
}

/* ==================== BUSCAS ==================== */

/* Inclui os removidos: o codigo de um produto removido nao pode ser reaproveitado */
int buscarPorCodigo(struct Produto lista[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (lista[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

/* Igual a buscarPorCodigo, mas trata produto removido (ativo == 0) como inexistente */
int buscarAtivoPorCodigo(struct Produto lista[], int total, int codigo) {
    int pos;

    pos = buscarPorCodigo(lista, total, codigo);
    if (pos != -1 && lista[pos].ativo == 0) {
        return -1;
    }
    return pos;
}

/* Texto nao se compara com ==, por isso o strcmp */
int buscarPorNome(struct Produto lista[], int total, char nome[]) {
    int i;
    for (i = 0; i < total; i++) {
        if (lista[i].ativo == 1 && strcmp(lista[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

/* ==================== EXIBICAO ==================== */

/* Recebe tambem a lista de categorias para mostrar o NOME da categoria */
void exibirProduto(struct Produto p, struct Categoria cats[], int totalCats) {
    int posCat;

    printf("Codigo: %d\n", p.codigo);
    printf("Nome: %s\n", p.nome);
    printf("Prateleira: %c\n", p.prateleira);
    printf("Preco unitario: R$ %.2f\n", p.preco);
    printf("Quantidade em estoque: %d\n", p.quantidade);

    posCat = buscarCategoriaPorCodigo(cats, totalCats, p.categoria_codigo);
    if (posCat != -1) {
        printf("Categoria: %s\n", cats[posCat].nome);
    } else {
        printf("Categoria: desconhecida\n");
    }

    printf("Disponivel para venda: %d", p.disponivel);
    if (p.disponivel == 1) {
        printf(" (Sim)\n");
    } else {
        printf(" (Nao)\n");
    }
}

/* ==================== LEITURA DOS CAMPOS (com validacao) ==================== */

/* Codigo: positivo (util) e nao repetido (depende da lista, entao fica aqui) */
static int lerCodigoProduto(struct Produto lista[], int total) {
    int codigo;

    do {
        printf("Codigo: ");
        codigo = lerInteiro(0);

        if (!inteiroPositivo(codigo)) {
            printf("Codigo invalido! Digite um numero positivo.\n");
        } else if (buscarPorCodigo(lista, total, codigo) != -1) {
            printf("Ja existe um produto com esse codigo! Digite outro.\n");
            codigo = 0;
        }
    } while (!inteiroPositivo(codigo));

    return codigo;
}

static void lerNomeProduto(char nome[]) {
    do {
        printf("Nome: ");
        lerTexto(nome, 50);

        if (!textoPreenchido(nome)) {
            printf("O nome nao pode ficar em branco!\n");
        } else if (!textoSemCaractere(nome, ';')) {
            printf("O nome nao pode ter ponto e virgula (;)!\n");
            nome[0] = '\0';
        }
    } while (!textoPreenchido(nome));
}

static char lerPrateleira(void) {
    char prateleira;

    do {
        printf("Prateleira (A, B, C ou D): ");
        prateleira = lerLetraMaiuscula();

        if (!letraPermitida(prateleira, "ABCD")) {
            printf("Prateleira invalida! Use apenas A, B, C ou D.\n");
        }
    } while (!letraPermitida(prateleira, "ABCD"));

    return prateleira;
}

static float lerPreco(void) {
    float preco;

    do {
        printf("Preco unitario: ");
        preco = lerDecimal(0);

        if (!decimalPositivo(preco)) {
            printf("Preco invalido! Tem que ser maior que zero.\n");
        }
    } while (!decimalPositivo(preco));

    return preco;
}

static int lerQuantidadeInicial(void) {
    int quantidade;

    do {
        printf("Quantidade em estoque: ");
        quantidade = lerInteiro(-1);

        if (!inteiroNaoNegativo(quantidade)) {
            printf("Quantidade invalida! Nao pode ser negativa.\n");
        }
    } while (!inteiroNaoNegativo(quantidade));

    return quantidade;
}

/* Categoria: o codigo precisa existir na lista de categorias */
static int lerCategoriaDoProduto(struct Categoria cats[], int totalCats) {
    int codigo;
    int posCat;

    printf("\nCategorias cadastradas:\n");
    mostrarCategorias(cats, totalCats);

    do {
        printf("Codigo da categoria: ");
        codigo = lerInteiro(0);

        posCat = buscarCategoriaPorCodigo(cats, totalCats, codigo);
        if (posCat == -1) {
            printf("Categoria inexistente! Escolha um codigo da lista.\n");
        }
    } while (posCat == -1);

    return codigo;
}

/* ==================== OPERACOES ==================== */

int cadastrarProduto(struct Produto lista[], int total, struct Categoria cats[], int totalCats) {
    struct Produto novo;

    printf("\n=== CADASTRAR PRODUTO ===\n");

    if (total >= MAX_PRODUTOS) {
        printf("Lista cheia! Nao e possivel cadastrar mais produtos (maximo %d).\n", MAX_PRODUTOS);
        return total;
    }

    /* Sem categoria nao tem como cadastrar produto */
    if (totalCats == 0) {
        printf("Nenhuma categoria cadastrada! Cadastre uma categoria antes (menu 6).\n");
        return total;
    }

    novo.codigo = lerCodigoProduto(lista, total);
    lerNomeProduto(novo.nome);
    novo.prateleira = lerPrateleira();
    novo.preco = lerPreco();
    novo.quantidade = lerQuantidadeInicial();
    novo.categoria_codigo = lerCategoriaDoProduto(cats, totalCats);
    novo.disponivel = calcularDisponibilidade(novo.quantidade);
    novo.ativo = 1; /* produto novo comeca ativo */

    lista[total] = novo;
    total = total + 1;

    printf("\n--- Produto cadastrado com sucesso! ---\n");
    exibirProduto(lista[total - 1], cats, totalCats);

    return total;
}

void listarProdutos(struct Produto lista[], int total, struct Categoria cats[], int totalCats) {
    int i;
    int ativos = 0;
    int mostrados = 0;

    printf("\n=== LISTA DE PRODUTOS ===\n");

    for (i = 0; i < total; i++) {
        if (lista[i].ativo == 1) {
            ativos++;
        }
    }

    if (ativos == 0) {
        printf("Nenhum produto foi cadastrado.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        if (lista[i].ativo == 1) { /* pula os removidos */
            mostrados++;
            printf("\n--- Produto %d de %d ---\n", mostrados, ativos);
            exibirProduto(lista[i], cats, totalCats);
        }
    }
}

void pesquisarProduto(struct Produto lista[], int total, struct Categoria cats[], int totalCats) {
    int tipo;
    int codigo;
    char nome[50];
    int posicao;

    printf("\n=== PESQUISAR PRODUTO ===\n");
    printf("1 - Por codigo\n");
    printf("2 - Por nome\n");
    printf("Escolha: ");
    tipo = lerInteiro(0);

    if (tipo == 1) {
        printf("Digite o codigo: ");
        codigo = lerInteiro(-1);
        posicao = buscarAtivoPorCodigo(lista, total, codigo);
    } else if (tipo == 2) {
        printf("Digite o nome: ");
        lerTexto(nome, 50);
        posicao = buscarPorNome(lista, total, nome);
    } else {
        printf("Opcao de pesquisa invalida!\n");
        return;
    }

    if (posicao == -1) {
        printf("Nenhum produto foi encontrado.\n");
    } else {
        printf("\n--- Produto encontrado ---\n");
        exibirProduto(lista[posicao], cats, totalCats);
    }
}

/* Entrada ou saida de itens no estoque de um produto ja cadastrado */
void alterarEstoque(struct Produto lista[], int total, struct Categoria cats[], int totalCats) {
    int codigo;
    int posicao;
    int tipo;
    int quantidade;

    printf("\n=== ALTERAR ESTOQUE ===\n");

    printf("Codigo do produto: ");
    codigo = lerInteiro(-1);

    posicao = buscarAtivoPorCodigo(lista, total, codigo);
    if (posicao == -1) {
        printf("Nenhum produto foi encontrado com esse codigo.\n");
        return; /* volta ao menu sem pedir a quantidade */
    }

    printf("\nProduto selecionado: %s (estoque atual: %d)\n", lista[posicao].nome, lista[posicao].quantidade);

    do {
        printf("1 - Entrada (chegada de mercadoria)\n");
        printf("2 - Saida (venda ou retirada)\n");
        printf("Escolha: ");
        tipo = lerInteiro(0);

        if (tipo != 1 && tipo != 2) {
            printf("Opcao invalida! Digite 1 ou 2.\n");
        }
    } while (tipo != 1 && tipo != 2);

    do {
        printf("Quantidade: ");
        quantidade = lerInteiro(0);

        if (!inteiroPositivo(quantidade)) {
            printf("Quantidade invalida! Digite um numero maior que zero.\n");
        }
    } while (!inteiroPositivo(quantidade));

    if (tipo == 1) {
        lista[posicao].quantidade = lista[posicao].quantidade + quantidade;
    } else {
        /* Saida: nao pode deixar o estoque negativo */
        if (quantidade > lista[posicao].quantidade) {
            printf("Saida maior que o estoque atual (%d)! Operacao nao realizada.\n", lista[posicao].quantidade);
            return;
        }
        lista[posicao].quantidade = lista[posicao].quantidade - quantidade;
    }

    /* Recalcula a disponibilidade com a mesma regra do cadastro */
    lista[posicao].disponivel = calcularDisponibilidade(lista[posicao].quantidade);

    printf("\n--- Estoque atualizado com sucesso! ---\n");
    exibirProduto(lista[posicao], cats, totalCats);
}

/* Exclusao logica: marca o produto como inativo (ativo = 0) */
void removerProduto(struct Produto lista[], int total) {
    int codigo;
    int posicao;

    printf("\n=== REMOVER PRODUTO ===\n");

    printf("Codigo do produto: ");
    codigo = lerInteiro(-1);

    posicao = buscarAtivoPorCodigo(lista, total, codigo);
    if (posicao == -1) {
        printf("Nenhum produto foi encontrado com esse codigo.\n");
        return;
    }

    lista[posicao].ativo = 0;
    printf("Produto \"%s\" removido com sucesso!\n", lista[posicao].nome);
}

/* ==================== ARQUIVO ==================== */

/* Salva todos os produtos, inclusive os removidos */
void salvarProdutos(struct Produto lista[], int total) {
    FILE *arq;
    int i;

    arq = fopen(ARQ_PRODUTOS, "w");
    if (arq == NULL) {
        printf("Aviso: nao foi possivel salvar o arquivo %s\n", ARQ_PRODUTOS);
        return;
    }
    for (i = 0; i < total; i++) {
        fprintf(arq, "%d;%s;%c;%.2f;%d;%d;%d;%d\n",
                lista[i].codigo, lista[i].nome, lista[i].prateleira,
                lista[i].preco, lista[i].quantidade, lista[i].disponivel,
                lista[i].categoria_codigo, lista[i].ativo);
    }
    fclose(arq);
}

/* Se o arquivo nao existir (primeira vez), devolve 0 e a lista comeca vazia */
int carregarProdutos(struct Produto lista[]) {
    FILE *arq;
    char linha[200];
    int total = 0;

    arq = fopen(ARQ_PRODUTOS, "r");
    if (arq == NULL) {
        return 0;
    }
    while (total < MAX_PRODUTOS && fgets(linha, sizeof(linha), arq) != NULL) {
        lista[total].ativo = 1; /* linhas antigas, sem o campo ativo, contam como ativas */
        if (sscanf(linha, "%d;%49[^;];%c;%f;%d;%d;%d;%d",
                   &lista[total].codigo, lista[total].nome, &lista[total].prateleira,
                   &lista[total].preco, &lista[total].quantidade,
                   &lista[total].disponivel, &lista[total].categoria_codigo,
                   &lista[total].ativo) >= 7) {
            total++;
        }
    }
    fclose(arq);
    return total;
}
