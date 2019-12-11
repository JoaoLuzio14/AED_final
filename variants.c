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
  int i, j, resultado = 14, *countlinhas, *countcolunas, tendasdomapa = 0, ignoradas = 0, *vectorcoords, arvoreatual = 0;
  /*Contadores de tendas por linhas e tendas por coluna*/
  countlinhas = (int*) calloc(maps->L ,sizeof(int));
  countcolunas = (int*) calloc(maps->C, sizeof(int));
  /*Vector que guarda as coordenadas das tendas*/
  vectorcoords = (int*) calloc(maps->ArvoresTotal + 1, sizeof(int));
  /*Análise de cada elemento do mapa*/
  for(i = 0;i < maps->L;i++){
    //printf("\n");
    for(j = 0;j < maps->C;j++){
      if(maps->mapa[i][j] == 'A'){
        resultado = varianteB(maps, i, j);
        if(resultado == 1){
          ignoradas++; //Árvore que pode ser ignorada!
          if(ignoradas > (maps->ArvoresTotal - maps->TendasTotal)){
            free(vectorcoords);
            free(countlinhas);
            free(countcolunas);
            return -1; //Impossivél
          }
        }
        else if(resultado == 2){
          vectorcoords[arvoreatual] = (i * maps->C) + j;
          //printf("%d\n", vectorcoords[arvoreatual]);
          arvoreatual++;
        }
        else if(resultado == -1){
          free(vectorcoords);
          free(countlinhas);
          free(countcolunas);
          return -1;
        }
      //printf("%c", maps->mapa[i][j]);
      }
    }
  }
  vectorcoords[arvoreatual] = -1;
  //printf("\n");
  if(tendasdomapa != 0) exit(0); //Neste caso não funciona!
  /*Colocação Recursiva de Tendas*/
  resultado = PlaceTents(maps, 0, vectorcoords, countlinhas, countcolunas, tendasdomapa, ignoradas);

  free(vectorcoords);
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
int PlaceTents(Mapa *maps, int pos, int *vector, int *countX, int *countY, int counttendas, int ignoradas){
  int nextX, nextY, verif = 0, resultado = 0;
  /*Verifica se todas a tentas já foram colocadas (Mapa Resolvido!)*/
  if(counttendas >= maps->TendasTotal) return 1; // Resolvido!!!
  else if(vector[pos] == -1) return -1; //Não Existem mais árvores possivéis
  /*Atribuição da próxima coordenada*/
  nextX = vector[pos] / maps->C;
  nextY = vector[pos] % maps->C;
  if((nextX >= 2) && (maps->TendasLinhas[nextX - 2] != countX[nextX - 2])) return -1; //Verifica se a linha já está preenchida.
  /*Coloca tenda numa das coordedas adjacentes da árvore, ou não coloca*/
  //pra cima
  if(nextX > 0){
    if(((verif = RodeiaTenda(maps, nextX - 1, nextY)) == 0) && (maps->TendasLinhas[nextX - 1] >= countX[nextX - 1] + 1) && (maps->TendasColunas[nextY] >= countY[nextY] + 1) && (maps->mapa[nextX - 1][nextY] != 'A') && (maps->mapa[nextX - 1][nextY] != 'T')){
      //printf("\nCima %d\n", counttendas + 1);
      maps->mapa[nextX - 1][nextY] = 'T'; //Coloca a Tenda
      countX[nextX - 1]++;
      countY[nextY]++;
      resultado = PlaceTents(maps, pos + 1, vector, countX, countY, counttendas + 1, ignoradas);
      if(resultado == 1) return 1; //Mapa Resolvido!
      else{
        maps->mapa[nextX - 1][nextY] = '.'; //Apaga a Tenda
        countX[nextX - 1]--;
        countY[nextY]--;
      }
    }
  }
  //pra esquerda
  if(nextY > 0){
    if(((verif = RodeiaTenda(maps, nextX, nextY - 1)) == 0) && (maps->TendasLinhas[nextX] >= countX[nextX] + 1) && (maps->TendasColunas[nextY - 1] >= countY[nextY - 1] + 1) && (maps->mapa[nextX][nextY - 1] != 'A') && (maps->mapa[nextX][nextY - 1] != 'T')){
      //printf("\nEsquerda %d\n", counttendas + 1);
      maps->mapa[nextX][nextY - 1] = 'T'; //Coloca a Tenda
      countX[nextX]++;
      countY[nextY - 1]++;
      resultado = PlaceTents(maps, pos + 1, vector, countX, countY, counttendas + 1, ignoradas);
      if(resultado == 1) return 1; //Mapa Resolvido!
      else{
        maps->mapa[nextX][nextY - 1] = '.'; //Apaga a Tenda
        countX[nextX]--;
        countY[nextY - 1]--;
      }
    }
  }
  //pra baixo
  if(nextX < (maps->L - 1)){
    if(((verif = RodeiaTenda(maps, nextX + 1, nextY)) == 0) && (maps->TendasLinhas[nextX + 1] >= countX[nextX + 1] + 1) && (maps->TendasColunas[nextY] >= countY[nextY] + 1) && (maps->mapa[nextX + 1][nextY] != 'A') && (maps->mapa[nextX + 1][nextY] != 'T')){
      //printf("\nBaixo %d\n", counttendas + 1);
      maps->mapa[nextX + 1][nextY] = 'T'; //Coloca a Tenda
      countX[nextX + 1]++;
      countY[nextY]++;
      resultado = PlaceTents(maps, pos + 1, vector, countX, countY, counttendas + 1, ignoradas);
      if(resultado == 1) return 1; //Mapa Resolvido!
      else{
        maps->mapa[nextX + 1][nextY] = '.'; //Apaga a Tenda
        countX[nextX + 1]--;
        countY[nextY]--;
      }
    }
  }
  //pra direita
  if(nextY < (maps->C - 1)){
    if(((verif = RodeiaTenda(maps, nextX, nextY + 1)) == 0) && (maps->TendasLinhas[nextX] >= countX[nextX] + 1) && (maps->TendasColunas[nextY + 1] >= countY[nextY + 1] + 1) && (maps->mapa[nextX][nextY + 1] != 'A') && (maps->mapa[nextX][nextY + 1] != 'T')){
      //printf("\nDireita %d\n", counttendas + 1);
      maps->mapa[nextX][nextY + 1] = 'T'; //Coloca a Tenda
      countX[nextX]++;
      countY[nextY + 1]++;
      resultado = PlaceTents(maps, pos + 1, vector, countX, countY, counttendas + 1, ignoradas);
      if(resultado == 1) return 1; //Mapa Resolvido!
      else{
        maps->mapa[nextX][nextY + 1] = '.'; //Apaga a Tenda
        countX[nextX]--;
        countY[nextY + 1]--;
      }
    }
  }
  //sem tenda
  if(ignoradas < (maps->ArvoresTotal - maps->TendasTotal)){
    resultado = PlaceTents(maps, pos + 1, vector, countX, countY, counttendas, ignoradas + 1);
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
  if(maps->TendasTotal == 0) return -1;
  /*Verifica: Possibilidade de linha/coluna?*/
  for(i = 0; i < maps->L; i++){
    if(maps->TendasLinhas[i] < 0) return 0;
    if(((maps->C % 2 == 0) && (maps->TendasLinhas[i] > maps->C/2)) || ((maps->C % 2 == 1) && (maps->TendasLinhas[i] > (maps->C/2) + 1))) return 0;
  }
  for(j = 0; j < maps->C; j++){
    if(maps->TendasColunas[j] < 0) return 0;
    if(((maps->L % 2 == 0) && (maps->TendasColunas[j] > maps->L/2)) || ((maps->L % 2 == 1) && (maps->TendasColunas[j] > (maps->L/2) + 1))) return 0;
  }
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
 * Retorna: Inteiro (4 resultados possíveis: '-1,1,2');
 * Efeitos Colaterais: (nada)
 *
 * Descrição: Inspeciona uma árvore do mapa de modo a verificar se é ignoravél
 *
 *****************************************************************************/
int varianteB(Mapa *maps, int cordX, int cordY){
  int arvoreadj = 0;
  /*Verifica: coordenada dentro dos limites do mapa?*/
  if((cordX < 0) || (cordX >= maps->L) || (cordY < 0) || (cordY >= maps->C)) return -1;
  arvoreadj = Adjobj(maps, cordX, cordY);
  if(arvoreadj == 2) return 1; //Árvore Ignoravél (Adjacentes bloqueiam)
  else if(arvoreadj == 1) return 2;//Árvore comum
  else return -1;
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
  int contadordearvores = 0;
  //pra cima
  if(a > 0){
    if((maps->mapa[a - 1][b] == 'A') || (maps->TendasLinhas[a - 1] == 0)){
      contadordearvores++;
    }
  }
  else contadordearvores++;
  //pra esquerda
  if(b > 0){
    if((maps->mapa[a][b - 1] == 'A') || (maps->TendasColunas[b -  1] == 0)){
      contadordearvores++;
    }

  }
  else contadordearvores++;
  //pra baixo
  if(a < (maps->L - 1)){
    if((maps->mapa[a + 1][b] == 'A') || (maps->TendasLinhas[a + 1] == 0)){
     contadordearvores++;
   }
  }
  else contadordearvores++;
  //pra direita
  if(b < (maps->C - 1)){
    if((maps->mapa[a][b + 1] == 'A') || (maps->TendasColunas[b + 1] == 0)){
      contadordearvores++;
    }
  }
  else contadordearvores++;
  //Retorno
  if (contadordearvores == 4) return 2;
  else return 1;
}
