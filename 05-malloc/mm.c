#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include "mm.h"
#include "memlib.h"

#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)
#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))


int mm_init(void)
{
  return 0;
}

void *mm_malloc(size_t size)
{
  int blk_size = ALIGN(size + SIZE_T_SIZE);
  size_t *header = mem_sbrk(blk_size);
  if (header == (void *)-1) {
    return NULL;
  } else {
    *header = blk_size | 1;
    return (char *)header + SIZE_T_SIZE;
  }
}

void mm_free(void *ptr)
{
  size_t *header = ptr - SIZE_T_SIZE;
  *header &= ~1L;
}

void *mm_realloc(void *ptr, size_t size)
{
  void *oldptr = ptr;
  void *newptr;
  size_t copySize;
    
  newptr = mm_malloc(size);
  if (newptr == NULL)
    return NULL;
  copySize = *(size_t *)((char *)oldptr - SIZE_T_SIZE);
  if (size < copySize)
    copySize = size;
  memcpy(newptr, oldptr, copySize);
  mm_free(oldptr);
  return newptr;
}
