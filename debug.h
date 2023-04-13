#ifndef DEBUG_H
#define DEBUG_H

#define debug false
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
   const char * file;
   int line;
   int size;
   void * ptr;
} MallocInfo;

extern unsigned num_malloc_records;
extern MallocInfo malloc_records[];

extern void * my_malloc(size_t size, const char * file, int line);
extern void my_free(void * ptr, const char * file, int line);
extern void audit_memory();

#define malloc(size) my_malloc(size, __FILE__, __LINE__)
#define free(ptr) my_free(ptr, __FILE__, __LINE__)

#endif
