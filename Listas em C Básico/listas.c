#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define Max 500

typedef struct{

 char nome[50];
 char endereco[50];
 }Cliente;

typedef struct{

 Cliente item[Max];
 int nElem;
 }Lista;

//iniciando a lista
void criarlista(Lista *lista){

   lista->nElem=0;
}

//inserindo um elemento no final da lista
void inserirFinal(Lista *lista, Cliente cli){
   lista->item[lista->nElen]=cli;
   lista->nElem=lista->nElem+1;
}

//inserir posição

void inserirPosicao(Lista *lista, pos, Cliente cli){

    int i;
    if(pos>=lista->nElen){
        inserirFinal(lista, cli);
    }
    else{

        for(i=lista->nElem; i > pos; i--){
            lista->item[i]=lista->item[-1];
        }

        lista->item[pos]=cli;
        lista->nElem=lista->nElem+1;
    }


}

int main(){

Lista lista;
criarlista(&lista);
Cliente cli;



return 0;
}
