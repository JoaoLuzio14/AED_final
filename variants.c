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
  int i, soma=0, resultado =0;

  if((maps->cordtenda[0]< 0) || (maps->cordtenda[0]>= maps->L) ||
  (maps->cordtenda[1]< 0) || (maps->cordtenda[1]>= maps->C)){
    return -1;
  }
  if(maps->mapa[maps->cordtenda[0]][maps->cordtenda[1]] == 'A') return 1;
  if(maps->mapa[maps->cordtenda[0]][maps->cordtenda[1]] == 'T') return 0;

  resultado = RodeiaTenda(maps, maps->cordtenda[0], maps->cordtenda[1]);
  if(resultado ==1) return 1;

  for(i=0 ; i<(maps->C) ; i++){
    if(maps->mapa[(maps->cordtenda[0])][i] == 'T') soma ++;
    if (soma > (maps->TendasLinhas[maps->cordtenda[0]])) return 1;
  }
  soma=0;
  for(i=0 ; i<(maps->L) ; i++){
    if(maps->mapa[i][maps->cordtenda[1]] == 'T') soma ++;
    if (soma > (maps->TendasColunas[maps->cordtenda[1]])) return 1;
  }
  resultado= Adjobj(maps, maps->cordtenda[0], maps->cordtenda[1], 'A');
  if(resultado==0) return 0;

  return 1;
}

int varianteC(Mapa *maps){
    int resultado = 0, i, j, *countlinhas, *countcolunas;

    countlinhas = (int*) calloc(sizeof(int) * maps->L);
    countcolunas = (int*) calloc(sizeof(int) * maps->C);

    for(i = 0;i < maps->L;i++){
      for(j = 0;j < maps->C;j++){
        if(maps->mapa[i][j] == 'T'){
          //Algoritmo
          countlinhas[i]++;
          countcolunas[j]++;
        }
        if(resultado == 1) break;
      }
      if(resultado == 1) break;
    }

    for(i = 0;i < maps->L;i++){
      if(countlinhas[i] > TendasLinhas[i]) resultado = 1;
      if(resultado == 1) break;
    }
    for(j = 0;j < maps->C;j++){
      if(countcolunas[j] > TendasColunas[j]) resultado = 1;
      if(resultado == 1) break;
    }

    return resultado;
}

int RodeiaTenda(Mapa *maps, int a, int b){
	int i,j;

  for(i=-1;i<2;i++){
	   for(j=-1;j<2;j++){
      if(((a== 0) && (i==-1)) || ((b==0) && (j==-1)) || ((maps->C == 1) && ((j==-1) || (j==1))) || ((maps->L == 1) && ((i==-1) || (i==1))) || ((a== ((maps->L) - 1)) && (i==1)) || ((b== ((maps->C) - 1)) && (j==1))) continue;
      if((maps->mapa[a+ i][b+j] == 'T')) return 1;
    }
  }

  return 0;
}

int Adjobj(Mapa *maps, int a, int b, char c){
	int i, j;

	for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(((a== 0) && (i==-1)) || ((maps->L == 1) && ((i==-1) || (i==1))) || ((maps->C == 1) && ((j==-1) || (j==1)))  || ((b==0) && (j==-1)) || ((a== ((maps->L) - 1)) && (i==1)) || ((b== ((maps->C) - 1)) && (j==1))) continue;
      if((maps->mapa[a+ i][b+j] == c)&&(((i==0)&&(j!=0))||((j==0) && (i!=0)))) return 0;
    }
  }

  return 1;
}
