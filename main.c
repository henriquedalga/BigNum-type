#include "BigNum.h"
#include "BigNum.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){

    BigNum* p = criar("21");
    BigNum* d = criar("2");
    BigNum* g = criar("0");
    //BigNum* soma = somar(p,d);
    //BigNum* outra = somar(g,p);
    //imprimir(d);
    //imprimir(p);
    //BigNum* sub = subtrair(p,d);
    //imprimir(outra);
    //imprimir(sub);
    //imprimir(d);
    
    //BigNum* div = dividir(p,d);
    BigNum* fat = fatorial(5);
    imprimir(fat);
    return 0;
}
