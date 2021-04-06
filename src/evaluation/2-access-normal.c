#include <stdio.h>
#include <stdlib.h>

#define INT_COUNT 100000
#define ACCESS_CYCLES 100

int
main(int argc, char** argv)
{
  int i = 0;
  int* memory = calloc(INT_COUNT, sizeof(*memory));
  if (memory == NULL) {
    fprintf(stderr, "Failed to allocate buffer.");
    return EXIT_FAILURE;
  }	
  for (i = 0; i < ACCESS_CYCLES; i++)
  {
    int index = rand() % INT_COUNT;
    memory[index]++;
  }
  return EXIT_SUCCESS;
}
