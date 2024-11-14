#include <stdio.h>
#include <stdlib.h>
#include "chess.h"
#include "gc.h"

struct dimensions {
  int height;
  int width;
};

struct dimensions Dimensions(char **picture) {
  struct dimensions d;
  int lineCount=0;
  while(picture[lineCount]!=0){lineCount++;}
  int colCount=0;
  while(picture[0][colCount]!=0){colCount++;}
  d.height = lineCount;
  d.width = colCount;
  return d;
}

void allocateMemory(char*** newFig, int rows, size_t cols){
  /* char** newFig; */
  memoryAlloc((void**)newFig, sizeof(char*)*(rows + 1));
  fprintf(stderr, "[DEBUG] Puntero nuevo newFig: %p\n", newFig);
  for(int i = 0; i < rows; i++)
    memoryAlloc((void**)&(*newFig)[i], sizeof(char)*(cols + 1));
  /* return newFig; */
}

void unlinkMemory(char*** fig){
  countMemoryEntries();
  for(int i = 0; (*fig)[i]; i++)
    unregisterPointer((void**) &((*fig)[i]));
  countMemoryEntries();
  unregisterPointer((void**)(fig));
  countMemoryEntries();
}

char** reverse(char** fig){
  int rows = 0;
  while(fig[++rows]);
  
  int cols = 0;
  while(fig[0][++cols]);

  char** newFig;
  allocateMemory(&newFig, rows, cols);

  for(int i = 0; fig[i]; i++){
    for(int j = 0; fig[0][j]; j++)
      newFig[i][j] = fig[i][j];
    newFig[i][cols] = 0;
  }
  newFig[rows] = 0;
  fprintf(stderr,"%p\n", &newFig);
  unlinkMemory(&newFig);
  /* unregisterPointer((void**)&newFig); */
  /* countMemoryEntries(); */
  return newFig;
}

char** repeatV(char **picture, int num){
  struct dimensions dim_picture = Dimensions(picture);
  dim_picture.height = dim_picture.height*num;
  char **result;
  allocateMemory(&result, dim_picture.height, dim_picture.width);
  for(int i=0;i<dim_picture.height;i++){
    for(int j=0;j<dim_picture.width;j++){
      result[i][j]=picture[i%(dim_picture.height/num)][j];
    }
    result[i][dim_picture.width]=0;
  }
  result[dim_picture.height]=0;
  unlinkMemory(&result);
  return result;
}

char** repeatH(char **figure, int num){
  struct dimensions dim_figure = Dimensions(figure);
  dim_figure.width = dim_figure.width * num;
  char **result;
  allocateMemory(&result, dim_figure.height, dim_figure.width);
  for (int i = 0; i < dim_figure.height; i++) {
    for (int j = 0; j<num; j++) {
      for (int k=0; k< dim_figure.width; k++) {
        result[i][k] = figure[i][k%(dim_figure.width/num)];
      }
    }
    result[i][dim_figure.width] = 0;
  }
  result[dim_figure.height] = 0;
  unlinkMemory(&result);
  return result;
}


