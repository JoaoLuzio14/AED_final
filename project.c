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

      //Implementar Solver Aqui
      resultado = Solver(mapatual);

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
