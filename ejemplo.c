#include "chess.h"
#include "figures.h"
#include "gc.h"
#include <stdio.h>

void display(){
  /*
  char** blackSquare = reverse(whiteSquare);
  interpreter(repeatH(repeatV(blackSquare, 8), 8));
  garbageCollector();
  */
  /*
  char** matrix;
  memoryAlloc((void**)matrix, sizeof(char*)*3);
  countMemoryEntries();
  unregisterPointer((void**)matrix);
  countMemoryEntries();
  garbageCollector();
  */

  float* var;
  memoryAlloc((void**)&var, sizeof(float)*5);
  unregisterPointer((void**)&var);
  garbageCollector();
}
