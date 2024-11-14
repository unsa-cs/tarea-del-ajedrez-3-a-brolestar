#include "chess.h"
#include "figures.h"
#include "gc.h"
#include <stdio.h>

void display(){

  char** blackSquare = reverse(whiteSquare);
  interpreter(repeatH(repeatV(blackSquare, 8), 8));
  countMemoryEntries();
  garbageCollector();
  countMemoryEntries();
}
