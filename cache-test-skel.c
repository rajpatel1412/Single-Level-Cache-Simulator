/*
Part 1 - Mystery Caches
*/

#include <stdlib.h>
#include <stdio.h>

#include "support/mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
  int size = 1;
  access_cache(0);
  while(access_cache(size)){
    size++;
  }
  return size;

}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  flush_cache();
  int c = 0;
  while(TRUE)
  {
    access_cache(c);
    for(int i = 0; i < c; i += block_size)
    {
      if(access_cache(i) == FALSE)
       return c;
    }
    c += block_size;
  }
  /*int initSize = block_size;
  access_cache(0);
  while(access_cache(0))
  {
    c = block_size;
    while(c <= initSize)
    {
      c += block_size;
      access_cache(c);
    }
    initSize += block_size;
  }*/
  return c;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
  /* YOUR CODE GOES HERE */
  
  int e;
  int size = 1;
  flush_cache();
  access_cache(0);
  //bool_t access = access_cache(0);
  while (access_cache(0))  
  {
    e = 0;
    for (int i = cache_size; i <= size; i += cache_size, e++) 
      access_cache(i); 
    size += cache_size;
  }
  return e;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0, 0);

  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
