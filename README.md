# Projeto Final - Sistema de Estoque (Linguagem C)

Sistema de estoque em linha de comando, com produtos, categorias, alteracao de estoque, exclusao logica e persistencia em arquivos de texto.

## Como compilar e executar

```
gcc main.c produto.c categoria.c util.c -o estoque
./estoque          (no Windows PowerShell: .\estoque.exe)
```

Execute sempre de dentro da pasta do projeto: os arquivos de dados sao criados nela.

## Organizacao do codigo

| Arquivo | Conteudo |
|---|---|
| `main.c` | So o menu principal: mostra o menu, le a opcao e chama a funcao correspondente |
| `produto.h` / `produto.c` | `struct Produto`, cadastro, listagem, pesquisa, alterar estoque, remover, arquivo de produtos e as validacoes que consultam a lista (codigo repetido, categoria inexistente) |
| `categoria.h` / `categoria.c` | `struct Categoria`, cadastro, listagem, submenu de categorias, arquivo de categorias e a validacao de codigo repetido |
| `util.h` / `util.c` | Leitura do teclado e validacoes genericas que nao dependem de lista (numero positivo, texto preenchido, letra permitida) |

## Menu

```
1 - Cadastrar Produto
2 - Listar Produtos
3 - Pesquisar Produto (por codigo ou por nome)
4 - Alterar Estoque de um Produto (entrada ou saida)
5 - Remover Produto
6 - Categorias (Cadastrar, Listar, Voltar)
7 - Sair
```

## Regras principais

- Produto: codigo (positivo e unico), nome (nao vazio), prateleira (A, B, C ou D), preco (> 0), quantidade (>= 0), categoria (precisa existir), disponibilidade e ativo.
- A disponibilidade nunca e digitada: e sempre calculada a partir da quantidade (1 se maior que zero, senao 0), no cadastro e a cada alteracao de estoque.
- Alterar estoque: entrada soma; saida subtrai, mas nunca deixa a quantidade negativa.
- Remover produto: exclusao logica (`ativo = 0`). O registro continua no arquivo e na lista em memoria, mas nao aparece em listagem nem em pesquisa. O codigo de um produto removido nao pode ser reutilizado.
- Todo produto mostra o NOME da categoria, nunca so o codigo.
- Limites: 50 produtos e 20 categorias. Categorias e produtos sao listas independentes.

## Arquivos de dados

- `categorias.txt`: `codigo;nome`
- `produtos.txt`: `codigo;nome;prateleira;preco;quantidade;disponivel;categoria;ativo`

Os dados sao carregados ao iniciar e salvos a cada alteracao e ao sair. Se um arquivo nao existir, a lista correspondente comeca vazia. Por isso os nomes nao podem conter `;`.
