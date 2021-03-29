#include "talloc/talloc.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ALLOCATION_SIZE 4096
#define REFERENCE_SIZE 1000000

typedef uint8_t SOME_MEMORY[ALLOCATION_SIZE];
typedef Reference SOME_REFERENCES[REFERENCE_SIZE];

int
main(int argc, char** argv)
{
  char label[32] = { 0 };
  int i = 0;
  Reference memory = TALLOC("main.memory", SOME_REFERENCES);
  if (memory == NULL) {
    fprintf(stderr, "Failed to allocate buffer.");
    return EXIT_FAILURE;
  }
  for (i = 0; i < REFERENCE_SIZE; i++) {
    sprintf(label, "main.memory%d", i);
    (TALLOC_DEREF(memory, SOME_REFERENCES))[i] = TALLOC(label, SOME_MEMORY);
  }
  for (i = 0; i < REFERENCE_SIZE; i++) {
    tallocFree((TALLOC_DEREF(memory, SOME_REFERENCES))[i]);
  }
  return EXIT_SUCCESS;
}
