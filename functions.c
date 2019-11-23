#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int lermapa(Mapa *maps, FILE *fp){
  int retval = 0, i;
  char cret;

  while(1){
    cret = fgetc(fp);
    if(feof(fp) != 0) return 1;
    if(((int) cret > 48 ) && ((int) cret < 58 )){
      fseek(fp, -1 , SEEK_CUR);
      break;
    }
  }
  retval = fscanf(fp,"%d %d ", &(maps->L), &(maps->C));
  if(retval != 2){
    if(feof(fp) == 0){
      return 1;
    }
    //printf("\nErro ao ler o ficheiro!\n");
    exit(0);
  }
  //printf("\n%d %d\n", maps->L, maps->C);

  /*Alocação de memória e leitura de dados relativamente ao número de tendas possivéis em cada linha e coluna*/
  maps->TendasLinhas = (int*) malloc(sizeof(int) * maps->L);
  if(maps->TendasLinhas == (int*) NULL){
    //printf("\nErro ao alocar memoria!\n");
    exit(0);
  }
  for(i = 0;i < maps->L;i++){
    retval = fscanf(fp,"%d ", &(maps->TendasLinhas[i]));
    if(retval != 1){
        //printf("\nErro ao ler o ficheiro!\n");
        exit(0);
    }
    //printf("%d ", maps->TendasLinhas[i]);
  }
  //printf("\n");
  maps->TendasColunas = (int*) malloc(sizeof(int) * maps->C);
  if(maps->TendasColunas == (int*) NULL){
    //printf("\nErro ao alocar memoria!\n");
    exit(0);
  }
  for(i = 0;i < maps->C;i++){
    retval = fscanf(fp,"%d ", &(maps->TendasColunas[i]));
    if(retval != 1){
        //printf("\nErro ao ler o ficheiro!\n");
        exit(0);
    }
    //printf("%d ", maps->TendasColunas[i]);
  }
  //printf("\n");
  /*Alocação de memória e leitura do mapa de jogo*/
  maps->mapa = (char**) malloc(sizeof(char*) * maps->L);
  for(i = 0;i < maps->L;i++){
    while(1){
      cret = fgetc(fp);
      if((cret == 'A') || (cret == '.') || (cret == 'T')){
        break;
      }
    }
    fseek(fp, -1 , SEEK_CUR);
    retval = fscanf(fp,"%ms", &(maps->mapa[i]));
    if(retval != 1){
      exit(0);
    }
    //printf("%s", maps->mapa[i]);
    //printf("\n");
  }
  return 0;
}

int freemapa(Mapa *maps){
  int retval = 0, i;
  for(i=0;i<maps->L; i++) free(maps->mapa[i]);
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
    //printf("\nErro ao abrir o ficheiro!\n");
    exit(0);
  }

  if(fp == NULL){
    //printf("\nErro ao abrir o ficheiro!\n");
    exit(0);
  }

  return fp;
}

FILE *writefile(FILE *fp, Mapa *maps, int resultado){
  int i;
  fprintf(fp, "%d %d ", maps->L, maps->C);
  fprintf(fp, "%d\n", resultado);
  if(resultado == 1){
    for(i = 0;i < maps->L;i++){
      fprintf(fp, "%s\n", maps->mapa[i]);
    }
  }
  fprintf(fp,"\n");
  return fp;
}
