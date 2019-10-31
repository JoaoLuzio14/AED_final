#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int varianteA(Mapa *maps){
  int sumlinhas = 0, sumcolunas = 0, ntendas = 0, narvores = 0, i, j;

  for(i = 0; i < maps->L; i++){
    sumlinhas += maps->TendasLinhas[i];
  }
  for(j = 0; j < maps->C; j++){
    sumcolunas += maps->TendasColunas[j];
  }
  if(sumlinhas != sumcolunas){
    return 0;
  }
  else{
    ntendas = sumlinhas;
  }

  for(i = 0; i < maps->L; i++){
    for(j = 0; j < maps->C; j++){
      if(maps->mapa[i][j] == 'A') narvores++;
    }
  }
  if(narvores != ntendas) return 0;

  return 1;
}

int varianteB(Mapa *maps){
  int resultado;

  resultado = 14;

  return resultado;
}

int varianteC(Mapa *maps){
    int resultado;

    resultado = 14;


    return resultado;
}
