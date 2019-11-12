/************************************************/
/*     Projecto AED - 1ª Fase de Submissão      */
/*          Semestre 1 - 2019/2020              */
/*João Luzio (IST193096) & José Reis (IST193105)*/
/*               IST - MEEC                     */
/************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

int main(int argc, char *argv[]){

    FILE *fpin = (FILE*) NULL;
    FILE *fpout = (FILE*) NULL;
    Mapa *mapatual;
    int retval = 0, resultado = 14;
    char *filename, *fileout, *token;

    if(argc != 2){
        //printf("\nNumero de argumentos errado ou insuficiente!\n");
        exit(0);
    }
    else{
        filename = (char*) malloc(strlen(argv[1]) + 1);
        strcpy(filename, argv[1]);
        token = strtok(filename, ".");
        token = strtok(NULL, ".");
        if((retval = strcmp(token, "camp0")) != 0){
            //printf("\nO ficheiro tem de ser de extensao '.camp0'!\n");
            exit(0);
        }
        fpin = openfile(fpin, argv[1], 0);
    }

    fileout = (char*) malloc(strlen(filename) + strlen(".tents0") + 1);
    strcpy(fileout, filename);
    free(filename);
    filename = strcat(fileout, ".tents0");
    fpout = openfile(fpout, filename, 1);
    free(fileout);

    mapatual = (Mapa*) malloc(sizeof(Mapa));

    while(feof(fpin) == 0){

      retval = lermapa(mapatual, fpin);
      if(retval != 0){
        if(retval == 1){
          break;
        }
        printf("\nErro ao ler o ficheiro!\n");
        exit(EXIT_FAILURE);
      }

      switch (mapatual->variante) {
        case 'A':
          resultado = varianteA(mapatual);
          if((resultado != 0) && (resultado != 1)){
            exit(0);
          }
          break;
        case 'B':
          resultado = varianteB(mapatual);
          if((resultado != 0) && (resultado != 1) && (resultado != -1)){
            exit(0);
          }
          break;
        case 'C':
          resultado = varianteC(mapatual);
          /*if((resultado != 0) && (resultado != 1)){
            exit(EXIT_FAILURE);
          }*/
          break;
        default:
          resultado = -1;
          break;
      }

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
