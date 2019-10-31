#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
/*Estrutura que guarda os
dados do mapa de jogo e
também outros detalhes já
relacionados com 'in game'*/
typedef struct Jogo{
    char **mapa; // Mapa original de jogo
    char variante; // Variante A,b ou C
    int L; // Número de linhas da matriz
    int C; // Número de Colunas da matriz
    int *TendasLinhas; //Número de Tendas por Linha
    int *TendasColunas; //Número de Tendas por Coluna
    int cordtenda[2]; //Guarda as coordenadas de uma tenda para ser testada;
}Mapa;

int varianteA(Mapa *maps);
int varianteB(Mapa *maps);
int varianteC(Mapa *maps);

int lermapa(Mapa *maps, FILE *fp);
int freemapa(Mapa *maps);
FILE *openfile(FILE *fp, char *filename, int mode);
FILE *writefile(FILE *fp, Mapa *maps, int resultado);

#endif // FUNCTIONS_H_INCLUDED
