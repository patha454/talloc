#include "talloc/talloc.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ALLOCATION_SIZE 4096

typedef uint8_t SOME_MEMORY[ALLOCATION_SIZE];

int
main(int argc, char** argv)
{
  int i = 0;
  if (argc < 2) {
    fprintf(stderr, "Usage requres an allocation count parameter.\n");
    exit(EXIT_FAILURE);
  }
  unsigned int repetitions = atoi(argv[1]);
  Reference* memory = calloc(repetitions, sizeof(*memory));
  if (memory == NULL) {
    fprintf(stderr, "Failed to allocate buffer.");
    return EXIT_FAILURE;
  }
  if (argc < 2) {
    fprintf(stderr, "An iteration count must be provided as a parameter.");
    return EXIT_FAILURE;
  }
  for (i = 0; i < repetitions; i++) {
    memory[i] = TALLOC(itoa(i), SOME_MEMORY);
  }
  for (i = 0; i < repetitions; i++) {
    tallocFree(memory[i]);
  }
  return EXIT_SUCCESS;
}
