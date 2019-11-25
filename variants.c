#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int Solver(Mapa *maps){
  int i, j, resultado = 14, *countlinhas, *countcolunas, tendasdomapa = 0;

  countlinhas = (int*) calloc(maps->L ,sizeof(int));
  countcolunas = (int*) calloc(maps->C, sizeof(int));

  for(i = 0;i < maps->L;i++){
    //printf("\n");
    for(j = 0;j < maps->C;j++){
      resultado = varianteB(maps, i, j);
      if(resultado == 2){
        countlinhas[i]++;
        countcolunas[j]++;
        tendasdomapa++;
      }
      else if(resultado == 0) maps->mapa[i][j] = 'O';
      //printf("%c", maps->mapa[i][j]);
    }
  }
  //printf("\n");

  resultado = PlaceTents(maps, 0, 0, countlinhas, countcolunas, tendasdomapa, 0, 0);

  if(resultado == 1){
    for(i = 0;i < maps->L;i++){
      for(j = 0;j < maps->C;j++){
        if(maps->mapa[i][j] == 'O') maps->mapa[i][j] = '.';
      }
    }
  }

  free(countlinhas);
  free(countcolunas);

  return resultado;
}

int PlaceTents(Mapa *maps, int cordX, int cordY, int *countX, int *countY, int counttendas, int init, int ignoradas){
  int nextX, nextY, breaker = 0, verif = 0, resultado = 0;

  if(counttendas >= maps->TendasTotal) return 1;

  nextX = cordX;
  if((cordX == 0) && (cordY == 0) && (init == 0)) nextY = cordY;
  else if(cordY == (maps->C - 1)){
    nextY = 0;
    nextX++;
  }
  else nextY = cordY + 1;

  while(nextX < maps->L){
    while(nextY < maps->C){
      if(maps->mapa[nextX][nextY] == 'A'){
        breaker = 1;
        break;
      }
      nextY++;
    }
    if(breaker == 1) break;
    nextY = 0;
    nextX++;
  }
  if(breaker == 0) return -1;
  //printf("New Cords: %d %d\n", nextX, nextY);


  //pra cima
  if(nextX > 0){
    if(maps->mapa[nextX - 1][nextY] == 'O'){
      if(((verif = RodeiaTenda(maps, nextX - 1, nextY)) == 0) && (maps->TendasLinhas[nextX - 1] >= countX[nextX - 1] + 1) && (maps->TendasColunas[nextY] >= countY[nextY] + 1)){
        //printf("\nCima %d\n", counttendas + 1);
        maps->mapa[nextX - 1][nextY] = 'T';
        countX[nextX - 1]++;
        countY[nextY]++;
        resultado = PlaceTents(maps, nextX, nextY, countX, countY, counttendas + 1, 1, ignoradas);
        if(resultado == 1) return 1;
        else{
          maps->mapa[nextX - 1][nextY] = 'O';
          countX[nextX - 1]--;
          countY[nextY]--;
        }
      }
    }
  }
  //pra esquerda
  if(nextY > 0){
    if(maps->mapa[nextX][nextY - 1] == 'O'){
      if(((verif = RodeiaTenda(maps, nextX, nextY - 1)) == 0) && (maps->TendasLinhas[nextX] >= countX[nextX] + 1) && (maps->TendasColunas[nextY - 1] >= countY[nextY - 1] + 1)){
        //printf("\nEsquerda %d\n", counttendas + 1);
        maps->mapa[nextX][nextY - 1] = 'T';
        countX[nextX]++;
        countY[nextY - 1]++;
        resultado = PlaceTents(maps, nextX, nextY, countX, countY, counttendas + 1, 1, ignoradas);
        if(resultado == 1) return 1;
        else{
          maps->mapa[nextX][nextY - 1] = 'O';
          countX[nextX]--;
          countY[nextY - 1]--;
        }
      }
    }
  }
  //pra baixo
  if(nextX < (maps->L - 1)){
    if(maps->mapa[nextX + 1][nextY] == 'O'){
      if(((verif = RodeiaTenda(maps, nextX + 1, nextY)) == 0) && (maps->TendasLinhas[nextX + 1] >= countX[nextX + 1] + 1) && (maps->TendasColunas[nextY] >= countY[nextY] + 1)){
        //printf("\nBaixo %d\n", counttendas + 1);
        maps->mapa[nextX + 1][nextY] = 'T';
        countX[nextX + 1]++;
        countY[nextY]++;
        resultado = PlaceTents(maps, nextX, nextY, countX, countY, counttendas + 1, 1, ignoradas);
        if(resultado == 1) return 1;
        else{
          maps->mapa[nextX + 1][nextY] = 'O';
          countX[nextX + 1]--;
          countY[nextY]--;
        }
      }
    }
  }
  //pra direita
  if(nextY < (maps->C - 1)){
    if(maps->mapa[nextX][nextY + 1] == 'O'){
      if(((verif = RodeiaTenda(maps, nextX, nextY + 1)) == 0) && (maps->TendasLinhas[nextX] >= countX[nextX] + 1) && (maps->TendasColunas[nextY + 1] >= countY[nextY + 1] + 1)){
        //printf("\nDireita %d\n", counttendas + 1);
        maps->mapa[nextX][nextY + 1] = 'T';
        countX[nextX]++;
        countY[nextY + 1]++;
        resultado = PlaceTents(maps, nextX, nextY, countX, countY, counttendas + 1, 1, ignoradas);
        if(resultado == 1) return 1;
        else{
          maps->mapa[nextX][nextY + 1] = 'O';
          countX[nextX]--;
          countY[nextY + 1]--;
        }
      }
    }
  }
  //sem tenda
  if(ignoradas < (maps->ArvoresTotal - maps->TendasTotal)){
    resultado = PlaceTents(maps, nextX, nextY, countX, countY, counttendas, 1, ignoradas + 1);
    if(resultado == 1) return 1;
  }
  //printf("\nArvore: %d\tCords: %d %d\n", counttendas, cordX, cordY);
  return  -1;
}

int varianteA(Mapa *maps){
  int sumlinhas = 0, sumcolunas = 0, narvores = 0, i, j;

  for(i = 0; i < maps->L; i++) sumlinhas += maps->TendasLinhas[i];
  for(j = 0; j < maps->C; j++) sumcolunas += maps->TendasColunas[j];
  if(sumlinhas != sumcolunas) return 0;
  else maps->TendasTotal = sumlinhas;

  for(i = 0; i < maps->L; i++){
    for(j = 0; j < maps->C; j++){
      if(maps->mapa[i][j] == 'A') narvores++;
    }
  }
  maps->ArvoresTotal = narvores;
  if(narvores < maps->TendasTotal) return 0;
  else return 1;
}

int varianteB(Mapa *maps, int cordX, int cordY){
  int tendavolta = 0, arvoreadj = 0;
  if((cordX < 0) || (cordX >= maps->L) || (cordY < 0) || (cordY >= maps->C)) return 1;
  if(maps->mapa[cordX][cordY] == 'A') return 1;
  else if(maps->mapa[cordX][cordY] == 'T') return 2;
  if((tendavolta = RodeiaTenda(maps, cordX, cordY)) == 1) return 1;
  else if((arvoreadj = Adjobj(maps, cordX, cordY)) == 1) return 1;
  else return 0;
}

int RodeiaTenda(Mapa *maps, int a, int b){
  int i,j;
  for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(((a == 0) && (i==-1)) || ((b==0) && (j==-1)) || ((a == ((maps->L) - 1)) && (i==1)) || ((b == ((maps->C) - 1)) && (j == 1))) continue;
      if((maps->mapa[a + i][b + j] == 'T') && ((i!=0) && (j!=0))) return 1;
    }
  }
  return 0;
}

int Adjobj(Mapa *maps, int a, int b){
  int detetorarvore = 0;
  //pra cima
  if(a > 0){
    if(maps->mapa[a - 1][b] == 'A') detetorarvore = 1;
  }
  //pra esquerda
  if(b > 0){
    if(maps->mapa[a][b - 1] == 'A') detetorarvore = 1;
  }
  //pra baixo
  if(a < (maps->L - 1)){
    if(maps->mapa[a + 1][b] == 'A') detetorarvore = 1;
  }
  //pra direita
  if(b < (maps->C - 1)){
    if(maps->mapa[a][b + 1] == 'A') detetorarvore = 1;
  }
  if(detetorarvore == 0) return 1;
  else return 0;
}
