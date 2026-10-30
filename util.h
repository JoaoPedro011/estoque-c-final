#ifndef UTIL_H
#define UTIL_H

/* Funcoes genericas: nao dependem de nenhuma lista (produtos ou categorias) */

/* ----- leitura do teclado ----- */
void limparBuffer(void);
int lerInteiro(int valorInvalido);          /* devolve valorInvalido se nao digitou um numero */
float lerDecimal(float valorInvalido);      /* idem, para numeros com virgula */
char lerLetraMaiuscula(void);               /* le um caractere e converte para maiuscula */
void lerTexto(char destino[], int tamanho); /* le texto com espacos, sem deixar lixo no teclado */

/* ----- validacoes genericas (devolvem 1 se valido, 0 se invalido) ----- */
int inteiroPositivo(int numero);            /* numero > 0 */
int decimalPositivo(float numero);          /* numero > 0 */
int inteiroNaoNegativo(int numero);         /* numero >= 0 */
int textoPreenchido(char texto[]);          /* tem pelo menos um caractere que nao seja espaco */
int textoSemCaractere(char texto[], char proibido);
int letraPermitida(char letra, char permitidas[]); /* a letra esta na lista de permitidas? */

#endif
