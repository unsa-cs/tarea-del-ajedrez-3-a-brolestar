#include "chess.h"
#include "figures.h"
#include "gc.h"

void display(){
  
  char** blackSquare = reverse(whiteSquare);
  interpreter(blackSquare);
  garbageCollector();
  
  /*
  char** matrix;
  memoryAlloc((void**)matrix, sizeof(char*)*3);
  countMemoryEntries();
  unregisterPointer((void**)matrix);
  countMemoryEntries();
  garbageCollector();
  */
}
