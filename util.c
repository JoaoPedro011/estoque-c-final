#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "util.h"

/* Se o teclado fechar (Ctrl+Z / Ctrl+D), encerra em vez de repetir a pergunta para sempre */
static void encerrarPorFimDaEntrada(void) {
    printf("\nEntrada encerrada. Saindo...\n");
    exit(0);
}

/* Limpa o que sobrou no teclado (o \n do Enter) depois de um scanf */
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* so descarta os caracteres */
    }
}

int lerInteiro(int valorInvalido) {
    int numero;
    int lidos;

    lidos = scanf("%d", &numero);
    if (lidos == EOF) {
        encerrarPorFimDaEntrada();
    }
    if (lidos != 1) {
        numero = valorInvalido; /* digitou letra ou simbolo */
    }
    limparBuffer();
    return numero;
}

float lerDecimal(float valorInvalido) {
    float numero;
    int lidos;

    lidos = scanf("%f", &numero);
    if (lidos == EOF) {
        encerrarPorFimDaEntrada();
    }
    if (lidos != 1) {
        numero = valorInvalido;
    }
    limparBuffer();
    return numero;
}

char lerLetraMaiuscula(void) {
    char letra;

    if (scanf(" %c", &letra) == EOF) {
        encerrarPorFimDaEntrada();
    }
    limparBuffer();
    return toupper((unsigned char)letra);
}

void lerTexto(char destino[], int tamanho) {
    if (fgets(destino, tamanho, stdin) == NULL) {
        encerrarPorFimDaEntrada();
    }
    if (strchr(destino, '\n') == NULL) {
        limparBuffer(); /* o texto era maior que o vetor, joga fora o resto */
    }
    destino[strcspn(destino, "\n")] = '\0';
}

int inteiroPositivo(int numero) {
    return numero > 0;
}

int decimalPositivo(float numero) {
    return numero > 0;
}

int inteiroNaoNegativo(int numero) {
    return numero >= 0;
}

int textoPreenchido(char texto[]) {
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        if (!isspace((unsigned char)texto[i])) {
            return 1;
        }
    }
    return 0;
}

int textoSemCaractere(char texto[], char proibido) {
    return strchr(texto, proibido) == NULL;
}

int letraPermitida(char letra, char permitidas[]) {
    return letra != '\0' && strchr(permitidas, letra) != NULL;
}
