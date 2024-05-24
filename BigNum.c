
#include "BigNum.h"
#include <stdlib.h>
#include <string.h>


BigNum* criar(char* numero){
    int recebe;
    int tamanho;
    BigNum* no = (BigNum*)malloc(sizeof(BigNum));
    if(numero[0] != '-'){
        tamanho = strlen(numero);
        no->tamanho = tamanho;
        recebe = numero[0] - '0';
        no->primeiro = recebe;
        no->sinal = 1;

        Algarismos* ultimo = (Algarismos*)malloc(sizeof(Algarismos));
        ultimo->prox = NULL;
        recebe = numero[tamanho-1] - '0';
        ultimo->number = recebe;
        no->ultimo = ultimo; 
        Algarismos *aux = ultimo;

        for(int i = tamanho-2; i >= 0; i--){
            Algarismos* novo = (Algarismos*)malloc(sizeof(Algarismos));
            recebe = numero[i] - '0';
            novo->number = recebe;
            novo->prox = NULL;
            aux->prox = novo;
            aux = aux->prox;
        
        }
    }
    else{
        tamanho = strlen(numero);
        tamanho--;
        no->tamanho = tamanho;
        recebe = numero[1] - '0';
        no->primeiro = recebe;
        no->sinal = -1;

        Algarismos* ultimo = (Algarismos*)malloc(sizeof(Algarismos));
        ultimo->prox = NULL;
        recebe = numero[tamanho] - '0';
        ultimo->number = recebe;
        no->ultimo = ultimo; 
        Algarismos *aux = ultimo;

        for(int i = tamanho-1; i > 0; i--){
            Algarismos* novo = (Algarismos*)malloc(sizeof(Algarismos));
            recebe = numero[i] - '0';
            novo->number = recebe;
            novo->prox = NULL;
            aux->prox = novo;
            aux = aux->prox;
            
        }
    }
    return no;
}

BigNum* adiciona(BigNum* a, int numero){
    
    Algarismos* novo = (Algarismos*)malloc(sizeof(Algarismos));
    novo->number = numero;
    novo->prox = NULL;
    a->primeiro = numero;
    Algarismos* aux = a->ultimo;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = novo;
    a->tamanho++;
    return a;
}

BigNum* somar(BigNum* a, BigNum* b){
    
    if(a->sinal != b->sinal){
        if(b->sinal == -1){
            b->sinal = b->sinal * -1;
            BigNum* novo = subtrair(a,b);
            b->sinal = b->sinal * -1;
            return novo;
        }
        else{
            a->sinal = a->sinal * -1;
            BigNum* novo = subtrair(b,a);
            a->sinal = a->sinal * -1;
            return novo;
        }
    }
    

    BigNum* novo = criar("0");
    int numero;
    int vaiUm = 0;
    int tamanhoMax = a->tamanho + b->tamanho;
    Algarismos* corrente1 = a->ultimo;
    Algarismos* corrente2 = b->ultimo;
    for(int t = 0; t < tamanhoMax; t++){

        numero = 0;
        
        if(corrente1 != NULL && corrente2 != NULL){
            numero = corrente1->number + corrente2->number + vaiUm;
        }
        else if(corrente2 == NULL && corrente1 == NULL){
            if(vaiUm == 0){
                return novo;
            }
            numero = vaiUm;

        }
        else if (corrente1 == NULL){
            numero = corrente2->number + vaiUm;
        }
        else{
            numero = corrente1->number + vaiUm;
            
        }

        if(corrente1 != NULL){
            corrente1 = corrente1->prox;
        }
        if(corrente2 != NULL){
            corrente2 = corrente2->prox;
        }

        vaiUm = 0;
        if(numero > 9){
            vaiUm = numero/10;
            numero = numero % 10;
        }
        if(t == 0){
            novo->primeiro = numero;
            novo->ultimo->number = numero;
            novo->ultimo->prox = NULL;
        }
        else{    
            novo = adiciona(novo, numero);
        }

    }
    if(a->sinal == -1){
        novo->sinal = -1;
    }
    return novo;
}

int comparar(BigNum* a, BigNum* b){
    if(a->tamanho > b->tamanho){
        return 0;
    }
    else if(b->tamanho > a->tamanho){
        return 1;
    }
    else{
        if(a->primeiro > b->primeiro){
            return 0;
        }
        else if(b->primeiro > a->primeiro){
            return 1;
        }
        else{
            
            for(int i = 0; i < a->tamanho; i++){
                Algarismos* correnteA = a->ultimo;
                Algarismos* correnteB = b->ultimo;
                for(int t = i+1; t < a->tamanho; t++){
                    correnteA = correnteA->prox;
                    correnteB = correnteB->prox;
                }
                if(correnteA->number > correnteB->number){
                    return 0;
                }
                else if(correnteB->number > correnteA->number){
                    return 1;
                }
                
            }
            return 3; //3 se forem iguais
        }
        
    }
    return 0;
} 

BigNum* subtrair(BigNum* a, BigNum* b) {
    
    if(a->sinal != b->sinal){
        b->sinal = b->sinal * -1;
        BigNum* novo = somar(a,b);
        b->sinal = b->sinal * -1;
        return novo;
    }

    int empresta = 0;
    int numero = 0;
    BigNum* novo = criar("0");
    Algarismos* correnteA = a->ultimo;
    Algarismos* correnteB = b->ultimo;
    int compara = comparar(a,b); //se 0 o primeiro é maior, se 1 o primeiro e menor
    if(compara == 3){
        return novo;
    }

    if(compara == 0){
        if(a->sinal == -1){
            novo->sinal = -1;
        }
        else{
            novo->sinal = 1;
        }
        for(int t = 0; t < a->tamanho; t++){
        //subtrai o b do a(a-b)
            if(correnteB != NULL){
                numero = correnteA->number - correnteB->number - empresta;
                
            }
            else if(correnteA != NULL){
                
                numero = correnteA->number - empresta;
                if(numero == 0){
                    return novo;
                }
            }
            empresta = 0;
            if(numero < 0){
                numero = numero + 10;
                empresta = 1;
            }
            if(t == 0){
                novo->primeiro = numero;
                novo->ultimo->number = numero;
                novo->tamanho = 1;
            }
            else{
            
                adiciona(novo, numero);
            }

            if(correnteB != NULL){
                correnteB = correnteB->prox;
            }
            if(correnteA != NULL){
                correnteA = correnteA->prox;
            }
            
        } 
    }
    else{
        //subtrai o a do b
        if(a->sinal == -1){
            novo->sinal = 1;
        }
        else{
            novo->sinal = -1;
        }
        for(int t = 0; t < a->tamanho; t++){

            if(correnteA != NULL){
                numero = correnteB->number - correnteA->number - empresta;
                
            }
            else if(correnteB != NULL){
                
                numero = correnteB->number - empresta;
            }
            empresta = 0;
            if(numero < 0){
                numero = numero + 10;
                empresta = 1;
            }
            if(t == 0){
                novo->primeiro = numero;
                novo->ultimo->number = numero;
                novo->tamanho = 1;
            }
            else{
            
                adiciona(novo, numero);
            }

            if(correnteA != NULL){
                correnteA = correnteA->prox;
            }
            if(correnteB != NULL){
                correnteB = correnteB->prox;
            }
            
        }

    }
    if(novo->primeiro == 0){
            Algarismos* aux = novo->ultimo;
            while(aux->prox->prox != NULL){
                aux = aux->prox;
            }
            aux->prox = NULL;
            novo->tamanho--;
    }
    return novo;
}

BigNum* shift10(BigNum* a){
    Algarismos* novo = malloc(sizeof(Algarismos));
    novo->number = 0;
    novo->prox = a->ultimo;
    a->ultimo = novo;
    a->tamanho++;

    return a;
}

BigNum* multiplicar(BigNum* a, BigNum* b) {
    int ax = a->sinal;
    int bx = b->sinal;
    a->sinal = 1;
    b->sinal = 1;
    BigNum* novo = criar("0");
    BigNum* A = a;
    Algarismos* auxB = b->ultimo;
    
    for(int i = 0; i < b->tamanho; i++){
        
        for(int t = 0; t < auxB->number; t++){
            novo = somar(novo, A);
        }
        if(auxB->prox != NULL){
            auxB = auxB->prox;
        }
        
        A = shift10(A);
    }
    novo->sinal = ax * bx;
    return novo;
}

BigNum* dividir(BigNum* a, BigNum* b){
    BigNum* N = criar("1");
    BigNum* zero = criar("0");
    BigNum* novo = criar("0");
    BigNum* um = criar("1");
    BigNum* A = criar("0");
    A = somar(zero,a);
    BigNum* B = criar("0"); 
    B = somar(zero,b);
    BigNum* antesB = criar("0");
    BigNum* antesN = criar("0");
    while(comparar(A,b) != 1){
        while(comparar(A, B) == 0){
            antesB = somar(zero,B);
            antesN = somar(zero,N);
            N = shift10(N);
            B = shift10(B);
        }
        novo = somar(novo,antesN);
        A = subtrair(A, antesB);
        B = somar(zero,b);
        N = somar(zero,um);
    }
    for(int t = 0; t < 2; t++){
        if(comparar(A,zero) == 3){
            return novo;
        }
        else{
            if(t == 0){
                novo->ultimo->virgula = 1;
            }
            BigNum* aux = criar("0");
            aux = shift10(A);
            novo = shift10(novo);
            if(comparar(aux,b) == 1){
                aux = shift10(aux);
                t++;
            }
            while(comparar(aux,b) != 1){
                while(comparar(aux, B) == 0){
                    
                    antesB = somar(zero,B);
                    antesN = somar(zero,N);
                    N = shift10(N);
                    B = shift10(B);
                }    
            novo = somar(novo,antesN);
            aux = subtrair(aux, antesB);
            B = somar(zero,b);
            N = somar(zero,um);
            }
            if(comparar(aux,zero) == 3){
                return novo;
            }
        }
    }
    return novo;
}

void imprimir(BigNum* lista){
    if(lista->sinal == -1){
        printf("-");
    }
    for(int i = 0; i < lista->tamanho; i++){
        Algarismos* aux = lista->ultimo;
        for(int t = i+1; t < lista->tamanho; t++){
            aux = aux->prox;
        }
        printf("%d", aux->number);
        if(aux->virgula == 1){
            printf(",");
        }
        aux = aux->prox;
    }
    printf("\n");
    return;
}

void destruir(BigNum* a){
    Algarismos* aux = a->ultimo;
    while(a->ultimo != NULL){
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        free(aux);
    }
    free(a);
    return;
}

char *  itoa ( int value, char * str )
{
    char temp;
    int i =0;
    while (value > 0) {
        int digito = value % 10;

        str[i] = digito + '0';
        value /= 10;
        i++;

    }
   i = 0;
   int j = strlen(str) - 1;

   while (i < j) {
      temp = str[i];
      str[i] = str[j];
      str[j] = temp;
      i++;
      j--;
   }
    return str;
}

BigNum* fatorial(int numero){
    BigNum* fat = criar("1");
    BigNum* um = criar("1");
    BigNum* conta = criar("0");
    for(int i = 1; i < numero; i++){
        BigNum* conta = somar(conta,um);
        fat = multiplicar(fat,conta);
    }
   return fat;
}







