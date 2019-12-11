/******************************************************************************
 *
 * Nome do Ficheiro: utility.h
 * Autor:  GR61 (AED 19/20) - João Luzio (IST193096) & José Reis (IST193105)
 * Última Revisão: 22 Nov 2019
 *
 * NOME
 *     Utility - Define a Estrutura do Mapa e as funções para o resolver
 *
 * DESCRIÇÃO
 *		Implementa uma estrtura (Jogo) e define dez funçãos auxiliares
 *
 *****************************************************************************/
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
    int L; // Número de Linhas da matriz
    int C; // Número de Colunas da matriz
    int *TendasLinhas; //Número de Tendas por Linha
    int *TendasColunas; //Número de Tendas por Coluna
    int TendasTotal; //Total de Tendas;
    int ArvoresTotal; //Total de Arvores;
}Mapa;

int varianteA(Mapa *maps);
int varianteB(Mapa *maps, int cordX, int cordY);
int Solver(Mapa *maps);
int PlaceTents(Mapa *maps, int pos, int *vector, int *countX, int *countY, int counttendas, int ignoradas);
int RodeiaTenda(Mapa *maps, int a, int b);
int Adjobj(Mapa *maps, int a, int b);

int lermapa(Mapa *maps, FILE *fp);
int freemapa(Mapa *maps);
FILE *openfile(FILE *fp, char *filename, int mode);
FILE *writefile(FILE *fp, Mapa *maps, int resultado);

#endif // FUNCTIONS_H_INCLUDED
