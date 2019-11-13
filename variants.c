#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

FILE *varianteA(Mapa *maps, FILE *fp, int *resultado){
  int sumlinhas = 0, sumcolunas = 0, ntendas = 0, narvores = 0, i, j;
  char obj;

  for(i = 0; i < maps->L; i++) sumlinhas += maps->TendasLinhas[i];
  for(j = 0; j < maps->C; j++) sumcolunas += maps->TendasColunas[j];
  if(sumlinhas != sumcolunas) return 0;
  else ntendas = sumlinhas;

  for(i = 0; i < maps->L; i++){
    for(j = 0; j < maps->C; j++){
      while(1){
        obj = fgetc(fp);
        if((obj == 'A') || (obj == '.') || (obj == 'T')){
          break;
        }
      }
      if(obj == 'A') narvores++;
    }
  }
  if(narvores != ntendas){
    *resultado = 0;
  }
  else{
    *resultado = 1;
  }
  return fp;
}

FILE *varianteB(Mapa *maps, FILE *fp, int *resultado){
  int i, j, arvoreadj = 0, tendadj = 0, *countlinhas, *countcolunas;
  char obj;

  if((maps->cordtenda[0]< 0) || (maps->cordtenda[0]>= maps->L) || (maps->cordtenda[1]< 0) || (maps->cordtenda[1]>= maps->C)){
    *resultado = -1;
    return fp;
  }

  countlinhas = (int*) calloc(maps->L, sizeof(int));
  countcolunas = (int*) calloc(maps->C, sizeof(int));

  for(i = 0;i < maps->L;i++){
    for(j = 0;j < maps->C;j++){
        while(1){
          obj = fgetc(fp);
          if((obj == 'A') || (obj == '.') || (obj == 'T')){
            if(obj == 'T'){
              countlinhas[i]++;
              countcolunas[j]++;
            }
            break;
          }
        }
        if(i == maps->cordtenda[0] - 1){
          if((j == maps->cordtenda[1] - 1) || (j == maps->cordtenda[1] + 1) || (j == maps->cordtenda[1])){
            if(obj == 'A') arvoreadj = 1;
            if(obj == 'T') tendadj = 1;
          }
        }
        else if(i == maps->cordtenda[0]){
          if(j == maps->cordtenda[1]){
            if(obj == 'A') *resultado = 3;
            else if(obj == 'T') *resultado = 2;
          }
          else if((j == maps->cordtenda[1] - 1) || (j == maps->cordtenda[1] + 1)){
            if(obj == 'A') arvoreadj = 1;
            if(obj == 'T') tendadj = 1;
          }
        }
        else if(i == maps->cordtenda[0] + 1){
          if((j == maps->cordtenda[1] - 1) || (j == maps->cordtenda[1] + 1) || (j == maps->cordtenda[1])){
            if(obj == 'A') arvoreadj = 1;
            if(obj == 'T') tendadj = 1;
          }
        }
    }
  }

  for(i = 0;i < maps->L;i++){
    if(countlinhas[i] > maps->TendasLinhas[i]) *resultado = 1;
    if(*resultado == 1) break;
  }
  for(j = 0;j < maps->C;j++){
    if(countcolunas[j] > maps->TendasColunas[j]) *resultado = 1;
    if(*resultado == 1) break;
  }

  free(countlinhas);
  free(countcolunas);

  if(*resultado == 2){
    *resultado = 0;
    return fp;
  }
  if(*resultado == 3){
    *resultado = 1;
    return fp;
  }
  if((arvoreadj == 0) || (tendadj == 1)) *resultado = 1;
  else *resultado = 0;

  return fp;
}

int varianteC(Mapa *maps){
    int resultado = 0, i, j, *countlinhas, *countcolunas, x, y,a1=0,a2=0, aux, soma,t=0, flag=0;

	   //printf("NOVO");
    countlinhas = (int*) calloc(maps->L ,sizeof(int));
    countcolunas = (int*) calloc(maps->C, sizeof(int));

    while(t!=0||flag==0){

      for(i = 0;i < maps->L;i++){
        for(j = 0;j < maps->C;j++){
  	       x = i;
  	       y = j;
  	       //printf("%d\n",resultado);
  	       if(((maps->mapa[i][j]== 'T')||(maps->mapa[i][j]== 't'))&& flag==0) t++;
           //printf("x:%d y:%d\n", x,y);
           while(maps->mapa[x][y] == 'T'){
  	          aux = AdjobjC(maps, x, y, 'A', &a1, &a2, &soma);
              //printf("t:%d\n", t);
              //printf("soma: %d\n", soma);
  	          if(soma==0){
  	             resultado = 1;
  	             break;
              }
  	          if(soma>1 && flag == 0)break;
  	          t--;
              //printf("passou a soma \n");
  	          maps->mapa[x][y] = 't';
              countlinhas[x]++;
              countcolunas[y]++;
              //printf("countlinhas[%d]=%d\n", x, countlinhas[x]);
  	          aux = RodeiaTenda(maps, x, y);
  	  	      if(aux ==1){
  		            resultado = 1;
  		            break;
  		        }
              maps->mapa[a1][a2]='a';
  	          aux = AdjobjC(maps, a1, a2, 'T', &x, &y, &soma);
           }
  	       a1=i;
  	       a2=j;
  	       while(maps->mapa[a1][a2]== 'A'){
  	          aux=AdjobjC(maps, a1, a2, 'T', &x, &y, &soma);
  		         if(soma!=1)break;
  	           //printf("soma %c: %d", maps->mapa[a1][a2], soma);
  	           //printf("detetou arvore singular\n");
  	           maps->mapa[a1][a2] = 'a';
  	           maps->mapa[x][y]='t';
  	           t--;
  		         aux=AdjobjC(maps, x, y, 'A', &a1, &a2, &soma);
  		         if(soma!=1) break;
  	       }
           if(resultado == 1) break;
        }
        if(resultado == 1) break;
      }
      //printf("\ntf:%d\n",t);
      //if(flag==1) exit(0);
      flag=1;
      //printf("%d\n",resultado);
      if(resultado==1) break;
    }
    for(i = 0;i < maps->L;i++){
      if(countlinhas[i] > maps->TendasLinhas[i]) resultado = 1;
      if(resultado == 1) break;
    }
    for(j = 0;j < maps->C;j++){
      if(countcolunas[j] > maps->TendasColunas[j]) resultado = 1;
      if(resultado == 1) break;
    }
	  free(countlinhas);
	  free(countcolunas);
    return resultado;
}

int RodeiaTenda(Mapa *maps, int a, int b){
  int i,j;
  for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(((a== 0) && (i==-1)) || ((b==0) && (j==-1)) || ((maps->C == 1) && ((j==-1) || (j==1))) || ((maps->L == 1) && ((i==-1) || (i==1))) || ((a== ((maps->L) - 1)) && (i==1)) || ((b== ((maps->C) - 1)) && (j==1))) continue;
      if((maps->mapa[a+ i][b+j] == 'T')) return 1;
    }
  }
  return 0;
}

int Adjobj(Mapa *maps, int a, int b, char c){
	int i, j;

	for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(((a== 0) && (i==-1)) || ((maps->L == 1) && ((i==-1) || (i==1))) || ((maps->C == 1) && ((j==-1) || (j==1)))  || ((b==0) && (j==-1)) || ((a== ((maps->L) - 1)) && (i==1)) || ((b== ((maps->C) - 1)) && (j==1))) continue;
      if((maps->mapa[a+ i][b+j] == c)&&(((i==0)&&(j!=0))||((j==0) && (i!=0)))) return 0;
    }
  }

  return 1;
}

int AdjobjC(Mapa *maps, int a, int b, char c, int *x, int *y, int *soma){
  int i, j;

  *soma = 0;

  for(i=-1;i<2;i++){
    for(j=-1;j<2;j++){
      if(((a== 0) && (i==-1)) || ((maps->L == 1) && ((i==-1) || (i==1))) || ((maps->C == 1) && ((j==-1) || (j==1)))  || ((b==0) && (j==-1)) || ((a== ((maps->L) - 1)) && (i==1)) || ((b== ((maps->C) - 1)) && (j==1))) continue;
      if((maps->mapa[a+ i][b+j] == c)&&(((i==0)&&(j!=0))||((j==0) && (i!=0)))){
        *x=a+i;
        *y=b+j;
        *soma = *soma +1;
      }
    }
  }
  if(*soma!=0)return 0;
  return 1;
}
