#include <stdlib.h>
#include "gc.h"
#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura MemoryEntry para el diccionario de la memoria reservada
typedef struct MemoryEntry{
  void* memory;
  void** pointer;
  struct MemoryEntry* next;
} MemoryEntry;

MemoryEntry* memoryList = NULL; // Lista enlazada para las entradas de memoria

int count(void* memory) {
  MemoryEntry* current = memoryList;
  int counter = 0;
  while(current) {
    if(current->memory == memory)
      counter++;
    current = current->next;
  }
  return counter;
}

void deleteMemoryEntry(MemoryEntry* node) {
  MemoryEntry* current = memoryList;
  MemoryEntry* prev = NULL;
  while(current) {
    if(current == node) {
      if(prev == NULL) {
        memoryList = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
    }
    prev = current;
    current = current->next;
  }
}

// Función de ayuda para crear una nueva entrada de memoria
MemoryEntry* createMemoryEntry(void* memory){
  MemoryEntry* entry = (MemoryEntry*)malloc(sizeof(MemoryEntry));
  entry->memory = memory;
  entry->pointer = NULL;
  entry->next = NULL;
  fprintf(stderr, "Creado puntero con memoria: %p\n", memory);
  return entry;
}

// Función para asignar memoria y registrar la entrada en el diccionario
void memoryAlloc(void** pointer, size_t size){
  *pointer = malloc(size);
  MemoryEntry *new_entry = createMemoryEntry(*pointer); 
  new_entry->pointer = pointer; 
  new_entry->next = memoryList;
  memoryList = new_entry;
}

// Función para agregar un puntero adicional que apunte a la misma memoria
void registerPointerToMemory(void** new_pointer, void* existing_memory){
  MemoryEntry* newNode = createMemoryEntry(existing_memory);
  newNode->pointer = new_pointer;
  newNode->next = memoryList;
  memoryList = newNode;
}

// Función para desvincular un puntero de la entrada de memoria correspondiente
void unregisterPointer(void** pointer){
  MemoryEntry* entry = memoryList;
  int counter = count(*pointer);
  while(entry && counter!=0){
    if(entry->pointer == pointer){
      fprintf(stderr, "Desvinculando memoria %p - %p\n", pointer, *pointer);
      if(counter > 1) {
        deleteMemoryEntry(entry);
      } else {
        entry->pointer = NULL;
      }
      return;
    } else {
      /* prev = entry; */
      entry = entry->next;
    }
  }
}

// Función de recolección de basura que libera memoria sin referencias activas
void garbageCollector(){
  MemoryEntry* current = memoryList;
  MemoryEntry* prev = NULL;
  while (current) {  
    if (current->pointer == NULL) {
      free(current->memory);
      if(prev == NULL){
        memoryList = current->next;
      } else {
        prev->next = current->next;
      }
      free(current);
      fprintf(stderr, "Liberando memoria: %p - MemoryEntry: %p\n", current->memory, current);
    }
    prev = current;
    current = current->next;
  }
}

int countMemoryEntries(){
  
}
