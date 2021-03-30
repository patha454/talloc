#include <stdio.h>
#include <stdlib.h>

#define ALLOCATION_SIZE 4096
#define REFERENCE_SIZE 1000000

int
main(int argc, char** argv)
{
  int i = 0;
  void** memory = calloc(REFERENCE_SIZE, sizeof(*memory));
  if (memory == NULL) {
    fprintf(stderr, "Failed to allocate buffer.");
    return EXIT_FAILURE;
  }
  for (i = 0; i < REFERENCE_SIZE; i++) {
    memory[i] = malloc(ALLOCATION_SIZE);
  }
  for (i = 0; i < REFERENCE_SIZE; i++) {
    free(memory[i]);
  }
  return EXIT_SUCCESS;
}
