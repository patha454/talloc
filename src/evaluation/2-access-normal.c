#include <stdio.h>
#include <stdlib.h>

#define INT_COUNT 100000

int
main(int argc, char** argv)
{
  int i = 0;
  int access_cycles = atoi(argv[1]);
  int* memory = calloc(INT_COUNT, sizeof(*memory));
  if (memory == NULL) {
    fprintf(stderr, "Failed to allocate buffer.");
    return EXIT_FAILURE;
  }	
  for (i = 0; i < access_cycles; i++)
  {
    int index = rand() % INT_COUNT;
    memory[index]++;
  }
  return EXIT_SUCCESS;
}
