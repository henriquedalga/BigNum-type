#include <stdio.h>

#ifndef BIG
#define BIG
typedef struct lista {
    struct lista* prox;
    int number;
    int virgula;
} Algarismos;

typedef struct bignum {
    int tamanho;
    int primeiro; //cópia da maior casa do numero, que se encontra no final da lista
    Algarismos* ultimo; //menor casa, que se encontra no inicio da lista
    int sinal;
} BigNum;


BigNum* criar(char*);

BigNum* adiciona(BigNum*,int);

BigNum* somar(BigNum*, BigNum*);

BigNum* subtrair(BigNum*, BigNum*);

BigNum* multiplicar(BigNum*, BigNum*);

BigNum* dividir(BigNum*, BigNum*);

void imprimir(BigNum*);

void destruir(BigNum*);

#endif