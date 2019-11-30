/******************************************************************************
 *
 * Nome do Ficheiro: variants.c
 * Autor:  GR61 (AED 19/20) - João Luzio (IST193096) & José Reis (IST193105)
 * Última Revisão: 27 Nov 2019
 *
 * NOME
 *     Variantes - 6 funções relacionadas com a resolução do mapa de jogo
 *
 * DESCRIÇÃO
 *		Implementa seis funçãos para validar o mapa e colocar tendas corretamanete
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

/******************************************************************************
 * Solver()
 *
 * Argumentos: Mapa de Jogo
 * Retorna: Resultado (Inteiro '1' ou '-1')
 * Efeitos Colaterais: Altera o mapa de jogo guardado em memória (Resolvido)
 *
 * Descrição: Encontra espaços aberto, árvores ignoráveis e inicia 'PlaceTents'
 *
 *****************************************************************************/
int Solver(Mapa *maps){
  int i, j, resultado = 14, *countlinhas, *countcolunas, tendasdomapa = 0, ignoradas = 0;
  /*Contadores de tendas por linhas e tendas por coluna*/
  countlinhas = (int*) calloc(maps->L ,sizeof(int));
  countcolunas = (int*) calloc(maps->C, sizeof(int));
  /*Análise de cada elemento do mapa*/
  for(i = 0;i < maps->L;i++){
    //printf("\n");
    for(j = 0;j < maps->C;j++){
      resultado = varianteB(maps, i, j);
      if(resultado == 2){
        countlinhas[i]++;
        countcolunas[j]++;
        tendasdomapa++; //Tem uma tenda já colocada...
      }
      else if(resultado == 3){
        maps->mapa[i][j] = 'a';
        ignoradas++; //Árvore que pode ser ignorada!
      }
      else if(resultado == 0) maps->mapa[i][j] = 'O'; //Pode ter tenda!
      //printf("%c", maps->mapa[i][j]);
    }
  }
  //printf("\n");
  if(tendasdomapa != 0) exit(0); //Neste caso não funciona!
  /*Colocação Recursiva de Tendas*/
  resultado = PlaceTents(maps, 0, 0, countlinhas, countcolunas, tendasdomapa, 0, ignoradas);
  /*Retifica o mapa de modo a retirar os marcadores auxiliares inseridos*/
  if(resultado == 1){
    for(i = 0;i < maps->L;i++){
      for(j = 0;j < maps->C;j++){
        if(maps->mapa[i][j] == 'O') maps->mapa[i][j] = '.';
        else if(maps->mapa[i][j] == 'a') maps->mapa[i][j] = 'A';
      }
    }
  }
  free(countlinhas);
  free(countcolunas);

  return resultado;
}

/******************************************************************************
 * PlaceTents()
 *
 * Argumentos: Mapa de Jogo, Coordenadas (X,Y), 4 Contadores e Inicializador
 * Retorna: Resultado (Inteiro '1' [mapa resolvido] ou '-1' [solução errada])
 * Efeitos Colaterais: Altera uma posição do mapa (coloca uma tenda)
 *
 * Descrição: Encontra uma Árvore e coloca-lhe uma tenda (ou não) se possivél
 *
 *****************************************************************************/
int PlaceTents(Mapa *maps, int cordX, int cordY, int *countX, int *countY, int counttendas, int init, int ignoradas){
  int nextX, nextY, breaker = 0, verif = 0, resultado = 0;

  /*Verifica se todas a tentas já foram colocadas (Mapa Resolvido!)*/
  if(counttendas >= maps->TendasTotal) return 1;
  /*Atribuição da próxima coordenada*/
  nextX = cordX;
  if((cordX == 0) && (cordY == 0) && (init == 0)) nextY = cordY;
  else if(cordY == (maps->C - 1)){
    nextY = 0;
    nextX++;
  }
  else nextY = cordY + 1;
  /*Procura a próxima árvore no mapa*/
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
  //Verifica se o mapa já acabou
  if(breaker == 0) return -1;
  //printf("New Cords: %d %d\n", nextX, nextY);

  /*Coloca tenda numa das coordedas adjacentes da árvore, ou não coloca*/
  //pra cima
  if(nextX > 0){
    if(maps->mapa[nextX - 1][nextY] == 'O'){
      if(((verif = RodeiaTenda(maps, nextX - 1, nextY)) == 0) && (maps->TendasLinhas[nextX - 1] >= countX[nextX - 1] + 1) && (maps->TendasColunas[nextY] >= countY[nextY] + 1)){
        //printf("\nCima %d\n", counttendas + 1);
        maps->mapa[nextX - 1][nextY] = 'T'; //Coloca a Tenda
        countX[nextX - 1]++;
        countY[nextY]++;
        resultado = PlaceTents(maps, nextX, nextY, countX, countY, counttendas + 1, 1, ignoradas);
        if(resultado == 1) return 1; //Mapa Resolvido!
        else{
          maps->mapa[nextX - 1][nextY] = 'O'; //Apaga a Tenda
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
        maps->mapa[nextX][nextY - 1] = 'T'; //Coloca a Tenda
        countX[nextX]++;
        countY[nextY - 1]++;
        resultado = PlaceTents(maps, nextX, nextY, countX, countY, counttendas + 1, 1, ignoradas);
        if(resultado == 1) return 1; //Mapa Resolvido!
        else{
          maps->mapa[nextX][nextY - 1] = 'O'; //Apaga a Tenda
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
        maps->mapa[nextX + 1][nextY] = 'T'; //Coloca a Tenda
        countX[nextX + 1]++;
        countY[nextY]++;
        resultado = PlaceTents(maps, nextX, nextY, countX, countY, counttendas + 1, 1, ignoradas);
        if(resultado == 1) return 1; //Mapa Resolvido!
        else{
          maps->mapa[nextX + 1][nextY] = 'O'; //Apaga a Tenda
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
        maps->mapa[nextX][nextY + 1] = 'T'; //Coloca a Tenda
        countX[nextX]++;
        countY[nextY + 1]++;
        resultado = PlaceTents(maps, nextX, nextY, countX, countY, counttendas + 1, 1, ignoradas);
        if(resultado == 1) return 1; //Mapa Resolvido!
        else{
          maps->mapa[nextX][nextY + 1] = 'O'; //Apaga a Tenda
          countX[nextX]--;
          countY[nextY + 1]--;
        }
      }
    }
  }
  //sem tenda
  if(ignoradas < (maps->ArvoresTotal - maps->TendasTotal)){
    resultado = PlaceTents(maps, nextX, nextY, countX, countY, counttendas, 1, ignoradas + 1);
    if(resultado == 1) return 1; //Mapa Resolvido!
  }
  //printf("\nArvore: %d\tCords: %d %d\n", counttendas, cordX, cordY);
  return  -1;
}

/******************************************************************************
 * varianteA()
 *
 * Argumentos: Mapa de Jogo
 * Retorna: Inteiro ('1' [solução possível?] ou '0' [sem solução])
 * Efeitos Colaterais: Guarda na estrutura o total de árvores e tendas do mapa
 *
 * Descrição: Verifica se o mapa pode ter solução ou se não tem solução de todo
 *
 *****************************************************************************/
int varianteA(Mapa *maps){
  int sumlinhas = 0, sumcolunas = 0, narvores = 0, i, j;
  /*Verifica: soma de tendas nas linhas igual à soma de tendas nas colunas?*/
  for(i = 0; i < maps->L; i++) sumlinhas += maps->TendasLinhas[i];
  for(j = 0; j < maps->C; j++) sumcolunas += maps->TendasColunas[j];
  if(sumlinhas != sumcolunas) return 0; //Sem solução
  else maps->TendasTotal = sumlinhas;
  /*Verifica: total de tendas menor ou igual ao total de árvores?*/
  for(i = 0; i < maps->L; i++){
    for(j = 0; j < maps->C; j++){
      if(maps->mapa[i][j] == 'A') narvores++;
    }
  }
  maps->ArvoresTotal = narvores;
  if(narvores < maps->TendasTotal) return 0; //Sem solução
  else return 1; //Solução possível
}

/******************************************************************************
 * varianteB()
 *
 * Argumentos: Mapa de Jogo, Coordenadas (X,Y)
 * Retorna: Inteiro (4 resultados possíveis: '0,1,2 ou 3');
 * Efeitos Colaterais: (nada)
 *
 * Descrição: Inspeciona um elemento do mapa de modo a 'rotolá-lo'
 *
 *****************************************************************************/
int varianteB(Mapa *maps, int cordX, int cordY){
  int tendavolta = 0, arvoreadj = 0;
  /*Verifica: coordenada dentro dos limites do mapa?*/
  if((cordX < 0) || (cordX >= maps->L) || (cordY < 0) || (cordY >= maps->C)) return 1;
  else if(maps->mapa[cordX][cordY] == 'T') return 2; //Tem uma tenda? Estranho.
  if((arvoreadj = Adjobj(maps, cordX, cordY)) == 1) return 1; //Sem Árvore Adj
  else if(arvoreadj == 2) return 3; //Árvore Ignoravél (Adjacentes bloqueiam)
  else if(maps->mapa[cordX][cordY] == 'A') return 1;//Árvore comum
  else if((tendavolta = RodeiaTenda(maps, cordX, cordY)) == 1) return 1;//???
  else return 0;//É um espaço susceptivél a albergar uma tenda!
}

/******************************************************************************
 * RodeiaTenda()
 *
 * Argumentos: Mapa de Jogo, Coordenadas (X,Y)
 * Retorna: Inteiro ('1' [Tem uma tenda à volta] ou '0' [Sem tendas a rodear]);
 * Efeitos Colaterais: (nada)
 *
 * Descrição: Inspeciona as 8 coordenadas á volta de um elemento e verica se
 *            são tendas, que é uma das restrições do jogo
 *
 *****************************************************************************/
int RodeiaTenda(Mapa *maps, int a, int b){
  int i,j;
  for(i=-1;i<=1;i++){
    for(j=-1;j<=1;j++){
      if(((a == 0) && (i==-1)) || ((b==0) && (j==-1)) || ((a == ((maps->L) - 1)) && (i==1)) || ((b == ((maps->C) - 1)) && (j == 1))) continue;
      if((maps->mapa[a + i][b + j] == 'T') && ((i!=0) || (j!=0))) return 1;
    }
  }
  return 0;
}

/******************************************************************************
 * AdjObj()
 *
 * Argumentos: Mapa de Jogo, Coordenadas (X,Y)
 * Retorna: Inteiro (3 reultados possíveis: '0,1 ou 2');
 * Efeitos Colaterais: (nada)
 *
 * Descrição: Inspeciona as 4 coordenadas adjacentes de um elemento do mapa de
 *            modo a verificar se este tem árvore adjacente, ou se é ignoravél
 *
 *****************************************************************************/
int Adjobj(Mapa *maps, int a, int b){
  int detetorarvore = 0, contadordearvores = 0;
  //pra cima
  if(a > 0){
    if((maps->mapa[a - 1][b] == 'A') || (maps->mapa[a - 1][b] == 'a')){
      detetorarvore = 1;
      contadordearvores++;
    }
  }
  else contadordearvores++;
  //pra esquerda
  if(b > 0){
    if((maps->mapa[a][b - 1] == 'A') || (maps->mapa[a][b - 1] == 'a')){
      detetorarvore = 1;
      contadordearvores++;
    }
  }
  else contadordearvores++;
  //pra baixo
  if(a < (maps->L - 1)){
    if((maps->mapa[a + 1][b] == 'A') || (maps->mapa[a + 1][b] == 'a')){
     detetorarvore = 1;
     contadordearvores++;
   }
  }
  else contadordearvores++;
  //pra direita
  if(b < (maps->C - 1)){
    if((maps->mapa[a][b + 1] == 'A') || (maps->mapa[a][b + 1] == 'a')){
      detetorarvore = 1;
      contadordearvores++;
    }
  }
  else contadordearvores++;
  //Retorno
  if((maps->mapa[a][b] == 'A') && (contadordearvores == 4)){
    return 2;
  }
  if(detetorarvore == 0) return 1;
  else return 0;
}
