#include "talloc/talloc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct TkRefTree* TkRefTree;

void tkRefTreeForEach(TkRefTree tree, void (*lambda)(Reference));

void printReference(Reference ref) {
  printf("[Reference 0x%llx <0x%llx>]\n", tkReferenceId(ref), tkReferenceType(ref));
}

int
main(void)
{
  tallocInit();
  Reference test = TALLOC("main.test", int);   /* NOLINT */
  Reference test2 = TALLOC("main.test2", int); /* NOLINT */
  TALLOC_DEREF(test, int) = 1;
  TALLOC_DEREF(test2, int) = 2;
  printf("1: %d, 2: %d\n", TALLOC_DEREF(test, int), TALLOC_DEREF(test2, int));
  printReference(test2);
  tallocForEachRef(printReference);
  return EXIT_SUCCESS;
}
