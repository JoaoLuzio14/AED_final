#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int lermapa(Mapa *maps, FILE *fp){
  int retval = 0, i, j;
  char variantes[] = {'A','B','C'};
  char cret;

  while(1){
    cret = fgetc(fp);
    if(feof(fp) != 0) return 1;
    if(((int) cret > 48 ) && ((int) cret < 58 )){
      fseek(fp, -1 , SEEK_CUR);
      break;
    }
  }


  retval = fscanf(fp,"%d %d %c", &(maps->L), &(maps->C), &(maps->variante));
  if(retval != 3){
    if(feof(fp) == 0){
      return 1;
    }
    printf("\nErro ao ler o ficheiro!\n");
    exit(EXIT_FAILURE);
  }
  printf("\n%d %d %c ", maps->L, maps->C, maps->variante);

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
        printf("%d %d", maps->cordtenda[0], maps->cordtenda[1]);
    }
  }
  printf("\n");
  /*Alocação de memória e leitura de dados relativamente ao número de tendas possivéis em cada linha e coluna*/
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
        while(1){
          cret = fgetc(fp);
          if((cret == 'A') || (cret == '.') || (cret == 'T')){
            break;
          }
        }
        maps->mapa[i][j] = cret;
        printf("%c", maps->mapa[i][j]);
    }
    printf("\n");
  }
  return 0;
}

int freemapa(Mapa *maps){
  int retval = 0, i;

  for(i=0;i<maps->L; i++){
    free(maps->mapa[i]);
  }

  free(maps->mapa);
  free(maps->TendasLinhas);
  free(maps->TendasColunas);

  return retval;
}

FILE *openfile(FILE *fp, char *filename, int mode){
  if(mode == 0){
    fp = fopen(filename, "r");
  }
  else if(mode == 1){
    fp = fopen(filename, "w");
  }
  else{
    printf("\nErro ao abrir o ficheiro!\n");
    exit(EXIT_FAILURE);
  }
  if(fp == NULL){
    printf("\nErro ao abrir o ficheiro!\n");
    exit(EXIT_FAILURE);
  }
  return fp;
}

FILE *writefile(FILE *fp, Mapa *maps, int resultado){

  fprintf(fp, "%d %d %c ", maps->L, maps->C, maps->variante);
  if(maps->variante == 'B'){
    fprintf(fp, "%d %d ", maps->cordtenda[0], maps->cordtenda[1]);
  }
  fprintf(fp, "%d\n", resultado);

  return fp;
}
