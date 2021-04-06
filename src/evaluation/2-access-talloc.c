#include "talloc/talloc.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INT_COUNT 100000
#define ACCESS_CYCLES 100

typedef Reference access_buffer_t[INT_COUNT];

int
main(int argc, char** argv)
{
  char label[32] = { 0 };
  int i = 0;
  Reference memory = TALLOC("main.memory", access_buffer_t);
  if (memory == NULL) {
    fprintf(stderr, "Failed to allocate buffer.");
    return EXIT_FAILURE;
  }
  for (i = 0; i < INT_COUNT; i++)
  {
    sprintf(label, "main.memory%d", i);
    TALLOC_DEREF(memory, access_buffer_t)[i] = TALLOC(label, int);  	
  }
  for (i = 0; i < ACCESS_CYCLES; i++)
  {
    int index = rand() % INT_COUNT;
    Reference ir = (TALLOC_DEREF(memory, access_buffer_t))[index];
    TALLOC_DEREF(ir, int) = TALLOC_DEREF(ir, int) + 1;
  }
  return EXIT_SUCCESS;
}
