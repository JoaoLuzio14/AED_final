/************************************************/
/*     Projecto AED - 2ª Fase de Submissão      */
/*          1º Semestre - 2019/2020             */
/*João Luzio (IST193096) & José Reis (IST193105)*/
/*               IST - MEEC                     */
/************************************************/

/******************************************************************************
 *
 * Nome do Ficheiro: project.c
 * Autor:  GR61 (AED 19/20) - João Luzio (IST193096) & José Reis (IST193105)
 * Última Revisão: 20 Nov 2019
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

/******************************************************************************
 * main()
 *
 * Argumentos: argc (número de argumentos inseridos), argv (vetor de argumentos)
 * Retorna: Inteiro ('0' - Validação)
 * Efeitos Colaterais: Cria um ficheiro de saída com extensão '.tents'
 *
 * Descrição: Resolve vários mapas (lidos de ficheiro) do jogo 'Trees & Tents'
 *
 *****************************************************************************/
int main(int argc, char *argv[]){

    FILE *fpin = (FILE*) NULL;
    FILE *fpout = (FILE*) NULL;
    Mapa *mapatual;
    int retval = 0, resultado = 14;
    char *filename, *fileout, *token;
    const char ch = '.';

    if(argc != 2){
        //printf("\nNumero de argumentos errado ou insuficiente!\n");
        exit(0);
    }
    else{
        filename = (char*) malloc(strlen(argv[1]) + 1);
        strcpy(filename, argv[1]);
        token = strrchr(filename, ch);
        if((retval = strcmp(token, ".camp")) != 0){
            exit(0);
        }
        else{
          token[0] = '\0';
        }
        fpin = openfile(fpin, argv[1], 0);
    }

    fileout = (char*) malloc(strlen(filename) + strlen(".tents") + 1);
    strcpy(fileout, filename);
    free(filename);
    filename = strcat(fileout, ".tents");
    fpout = openfile(fpout, filename, 1);
    free(fileout);


    mapatual = (Mapa*) malloc(sizeof(Mapa));

    while(feof(fpin) == 0){

      retval = lermapa(mapatual, fpin);
      if(retval != 0){
        if(retval == 1){
          break;
        }
        //printf("\nErro ao ler o ficheiro!\n");
        exit(0);
      }

      if((resultado = varianteA(mapatual)) == 0){
        fpout = writefile(fpout, mapatual, -1);
        retval = freemapa(mapatual);
        if(retval != 0){
          //printf("\nErro a libertar a memoria!");
          exit(0);
        }
        continue;
      }
      else if(resultado == -1){
        fpout = writefile(fpout, mapatual, 1);
        retval = freemapa(mapatual);
        if(retval != 0){
          //printf("\nErro a libertar a memoria!");
          exit(0);
        }
        continue;
      }

      resultado = Solver(mapatual); //Resolve o Mapa!

      fpout = writefile(fpout, mapatual, resultado);
      retval = freemapa(mapatual);
      if(retval != 0){
        //printf("\nErro a libertar a memoria!");
        exit(0);
      }
    }

    free(mapatual);
    fclose(fpin);
    fclose(fpout);

    exit(0);
    return 0;
}
