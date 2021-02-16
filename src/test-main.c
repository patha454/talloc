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
  Reference test = talloc("main.test", int);   /* NOLINT */
  Reference test2 = talloc("main.test2", int); /* NOLINT */
  tallocDeref(test, int) = 1;
  tallocDeref(test2, int) = 2;
  printf("1: %d, 2: %d\n", tallocDeref(test, int), tallocDeref(test2, int));
  printReference(test2);
  tallocForEachRef(printReference);
  return EXIT_SUCCESS;
}
