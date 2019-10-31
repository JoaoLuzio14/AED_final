#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int lermapa(Mapa *maps, FILE *fp){
  int retval = 0, i, j;
  char variantes[] = {'A','B','C'};
  char cret;

  retval = fscanf(fp,"%d %d %c", &(maps->L), &(maps->C), &(maps->variante));
  if(retval != 3){
    printf("\nErro ao ler o ficheiro!\n");
    exit(EXIT_FAILURE);
  }
  //printf("\n%d %d %c", maps->L, maps->C, maps->variante);

  if((maps->variante != variantes[0]) && (maps->variante != variantes[1]) && (maps->variante != variantes[2])){
    printf("\nEsta versao do projecto nao possui a variante '%c'!\n", maps->variante);
    free(maps);
    exit(EXIT_FAILURE);
  }
  else{
    if(maps->variante == variantes[1]){
        retval = fscanf(fp,"%d %d", &(maps->cordtenda[0]), &(maps->cordtenda[1]));
        if(retval != 2){
            printf("\nErro ao ler o ficheiro!\n");
            exit(EXIT_FAILURE);
        }
    }
    //while((cret = fgetc(fp)) != '\n');
  }
  /*Alocação de memŕia e leitura de dados relativamente ao número de tendas possivéis em cada linha e coluna*/
  maps->TendasLinhas = (int*) malloc(sizeof(int) * maps->L);
  if(maps->TendasLinhas == (int*) NULL){
    printf("\nErro ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }
  maps->TendasColunas = (int*) malloc(sizeof(int) * maps->C);
  if(maps->TendasColunas == (int*) NULL){
    printf("\nErro ao alocar memoria!\n");
    exit(EXIT_FAILURE);
  }
  for(i = 0;i < maps->L;i++){
    retval = fscanf(fp,"%d ", &(maps->TendasLinhas[i]));
    if(retval != 1){
        printf("\nErro ao ler o ficheiro!\n");
        exit(EXIT_FAILURE);
    }
    printf("%d ", maps->TendasLinhas[i]);
  }
  printf("\n");
  for(j = 0;j < maps->C;j++){
    retval = fscanf(fp,"%d ", &(maps->TendasColunas[j]));
    if(retval != 1){
        printf("\nErro ao ler o ficheiro!\n");
        exit(EXIT_FAILURE);
    }
    printf("%d ", maps->TendasColunas[j]);
  }
  printf("\n");
  /*Alocação de memória e leitura do mapa de jogo*/
  maps->mapa = (char**) malloc(sizeof(char*) * maps->L);
  for(i = 0;i < maps->L;i++){
    maps->mapa[i] = (char*) malloc(sizeof(char) * maps->C);
    for(j = 0;j < maps->C;j++){
        //retval = fscanf(fp,"%c", &(maps->mapa[i][j]));
        while(1){
          cret = fgetc(fp);
          if((cret == 'A') || (cret == '.') || (cret == 'T')){
            break;
          }
        }
        maps->mapa[i][j] = cret;
        /*if(retval != 1){
            printf("\nErro ao ler o ficheiro!\n");
            exit(EXIT_FAILURE);
        }*/
        printf("%c", maps->mapa[i][j]);
    }
    printf("\n");
  }
  return 0;
}

int freemapa(Mapa *maps){
  int retval = 0;


  return retval;
}

FILE *openfile(FILE *fp, char *filename){
  fp = fopen(filename, "r");
  if(fp == NULL){
    printf("\nErro ao abrir o ficheiro!\n");
    exit(EXIT_FAILURE);
  }
  return fp;
}
