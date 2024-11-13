#include <stdlib.h>
#include "gc.h"
#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura Node para manejar la lista de punteros en cada entrada de memoria
typedef struct PointerNode{
  void** pointer;
  struct PointerNode* next;
} PointerNode;

// Definición de la estructura MemoryEntry para el diccionario de la memoria reservada
typedef struct MemoryEntry{
  void* memory;
  PointerNode* pointers;
  struct MemoryEntry* next;
} MemoryEntry;

MemoryEntry* memoryList = NULL; // Lista enlazada para las entradas de memoria

// Función de ayuda para crear un nuevo nodo de puntero
PointerNode* createPointerNode(void** pointer){
  PointerNode* node = (PointerNode*)malloc(sizeof(PointerNode));
  node->pointer = pointer;
  node->next = NULL;
  fprintf(stderr, "PointerNode: %p apunta a %p\n" , node, *pointer);
  return node;
}

// Función de ayuda para crear una nueva entrada de memoria
MemoryEntry* createMemoryEntry(void* memory){
  MemoryEntry* entry = (MemoryEntry*)malloc(sizeof(MemoryEntry));
  entry->memory = memory;
  entry->pointers = NULL;
  entry->next = NULL;
  fprintf(stderr, "MemoryEntry creado %p\n", entry);
  return entry;
}

// Función para asignar memoria y registrar la entrada en el diccionario
void memoryAlloc(void** pointer, size_t size){
  *pointer = malloc(size);
  MemoryEntry *new_entry = createMemoryEntry(*pointer); 
  new_entry->pointers = createPointerNode(pointer); 
  new_entry->next = memoryList;
  memoryList = new_entry;
}

// Función para agregar un puntero adicional que apunte a la misma memoria
void registerPointerToMemory(void** new_pointer, void* existing_memory){
  
}

// Función para desvincular un puntero de la entrada de memoria correspondiente
void unregisterPointer(void** pointer){
  MemoryEntry* entry = memoryList;
  
  while(entry){
    PointerNode* current = entry->pointers; 
    PointerNode* prev = NULL;

    while(current){
      if(current->pointer == pointer){
        if(prev){
          prev->next = current->next;
        } else {
          entry->pointers = current->next;
        }
        free(current);
      }
      prev = current;
      current = current->next; 
    }
    entry = entry->next;
  }
}

// Función de recolección de basura que libera memoria sin referencias activas
void garbageCollector(){
  
}

int countMemoryEntries(){
  
}
