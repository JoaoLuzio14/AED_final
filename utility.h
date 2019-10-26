#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/*Estrutura que guarda os
dados do mapa de jogo e
também outros detalhes já
relacionados com 'in game'*/
typedef struct Jogo{
    char **mapa; // Mapa original de jogo
    char variante; // Variante A,b ou C
    int L; // Número de linhas da matriz
    int C; // Número de Colunas da matriz
    int cordtenda[2]; //Guarda as coordenadas de uma tenda para ser testada;
}Mapa;

#endif // FUNCTIONS_H_INCLUDED
