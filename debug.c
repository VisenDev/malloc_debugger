#include "../include/debug.h"

unsigned num_malloc_records = 0;
MallocInfo malloc_records[1024];


void * my_malloc(size_t size, const char * file, int line) {
   printf("MALLOC_DEBUG: %zu bytes allocated with malloc at line %i in file %s\n", size, line, file);


   #undef malloc
   void * result =  malloc(size);
   #define malloc(size) my_malloc(size)

   //store data on what has been malloced
   malloc_records[num_malloc_records].size = size;
   malloc_records[num_malloc_records].file = file;
   malloc_records[num_malloc_records].line = line;
   malloc_records[num_malloc_records].ptr = result;
   ++num_malloc_records;

   return result;
}

void my_free(void * ptr, const char * file, int line) {

   //parse thru malloc records until record with identical ptr is found
   for(int i = 0; i < num_malloc_records; i++){
      if(malloc_records[i].ptr == ptr){

         printf("MALLOC_DEBUG: %i bytes allocated at line %i in file %s were freed at line %i in file %s\n", malloc_records[i].size, malloc_records[i].line, malloc_records[i].file, line, file);

         //free data
         malloc_records[i] = malloc_records[num_malloc_records - 1];
         --num_malloc_records;

      }
   }

   #undef free
   free(ptr);
   #define free(ptr) my_free(ptr)
}

void audit_memory(){
   if(num_malloc_records != 0){
      //output all still existing malloc records

      fprintf(stderr, "\nMALLOC_ERROR: Memory leak(s)\n");

      for(int i = 0; i < num_malloc_records; i++){
         fprintf(stderr, "    • %d bytes allocated at line %i in file %s were not deallocated\n", malloc_records[i].size, malloc_records[i].line, malloc_records[i].file);
      }

      exit(1);
   }
}