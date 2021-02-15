#include "talloc/talloc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct TkRefTree* TkRefTree;

void tkRefTreeForEach(TkRefTree tree, void (*lambda)(Reference));

void printReference(Reference ref) {
  printf("[Reference 0x%lx <0x%lx>]\n", tkReferenceId(ref), tkReferenceType(ref));
}

int
main(void)
{
  tallocInit();
  Reference test = talloc("main.test", int);   /* NOLINT */
  Reference test2 = talloc("main.test2", int); /* NOLINT */
  printReference(test2);
  tallocForEachRef(printReference);
  return EXIT_SUCCESS;
}
