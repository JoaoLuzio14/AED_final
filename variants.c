#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int varianteA(Mapa *maps){
  int sumlinhas = 0, sumcolunas = 0, ntendas = 0, narvores = 0, i, j;

  for(i = 0; i < maps->L; i++) sumlinhas += maps->TendasLinhas[i];
  for(j = 0; j < maps->C; j++) sumcolunas += maps->TendasColunas[j];
  if(sumlinhas != sumcolunas) return 0;
  else ntendas = sumlinhas;

  for(i = 0; i < maps->L; i++){
    for(j = 0; j < maps->C; j++){
      if(maps->mapa[i][j] == 'A') narvores++;
    }
  }
  if(narvores != ntendas) return 0;
  return 1;
}

int varianteB(Mapa *maps){
  int i, j, soma=0, casoexL0=0, casoexC0=0, casoexLF=0, casoexCF=0;

  if((maps->cordtenda[0]< 0) || (maps->cordtenda[0]>= maps->L) ||
  (maps->cordtenda[1]< 0) || (maps->cordtenda[1]>= maps->C)){
    return -1;
  }

  if(maps->cordtenda[0]== 0)casoexL0=1;
  if(maps->cordtenda[1]==0) casoexC0=1;
  if(maps->cordtenda[0]== ((maps->L) - 1)) casoexLF=1;
  if(maps->cordtenda[0]== ((maps->C) - 1)) casoexCF=1;

  for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(((casoexL0==1) && (i==-1)) || ((casoexC0==1) && (j==-1)) || ((casoexLF==1) && (i==1)) || ((casoexCF==1) && (i==1))) continue;
      if(((maps->mapa[(maps->cordtenda[0])+ i][(maps->cordtenda[1])+j] == 'T') || (maps->mapa[(maps->cordtenda[0])][(maps->cordtenda[1])]=='T')) && (i!=0 && j!=0)) return 1;
    }
  }

  for(i=0 ; i<(maps->C) ; i++){
    if(maps->mapa[(maps->cordtenda[0])][i] == 'T') soma ++;
    if (soma == (maps->TendasLinhas[maps->cordtenda[0]])) return 1;
  }

  for(i=0 ; i<(maps->L) ; i++){
    if(maps->mapa[i][maps->cordtenda[1]] == 'T') soma ++;
    if (soma == (maps->TendasColunas[maps->cordtenda[1]])) return 1;
  }

  for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(((casoexL0==1) && (i==-1)) || ((casoexC0==1) && (j==-1)) || ((casoexLF==1) && (i==1)) || ((casoexCF==1) && (i==1))) continue;
      if((maps->mapa[(maps->cordtenda[0])+ i][(maps->cordtenda[1])+j] == 'A')&&(((i==0)&&(j!=0))||((j==0) && (i!=0)))) return 0;
    }
  }

  return 1;
}

int varianteC(Mapa *maps){
    int resultado;

    resultado = 14;


    return resultado;
}
