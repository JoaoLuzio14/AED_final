#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int main(int argc, char *argv[]){

    FILE *fp;
    Mapa *mapatual;
    char variantes[] = {'A','B','C'};
    int i,j;

    if(argc != 2){
        printf("\nNumero de argumentos errado ou insuficiente!\n");
    }
    else{
        fp = fopen(argv[1], "r");
        if(fp == (FILE*) NULL){
            printf("\nErro ao abrir o ficheiro!\n");
            exit(EXIT_FAILURE);
        }
    }

    mapatual = (Mapa*) malloc(sizeof(Mapa));

    fscanf(fp,"%d %d %c", &(mapatual->L), &(mapatual->C), &(mapatual->variante));



    printf("Hello world!\n");
    return 0;

}
