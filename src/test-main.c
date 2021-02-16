#include "talloc/talloc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct TkRefTree* TkRefTree;

void tkRefTreeForEach(TkRefTree tree, void (*lambda)(Reference));

void printReference(Reference ref) {
  printf("[Reference 0x%llx <0x%llx>]\n", tkReferenceId(ref), tkReferenceType(ref));
}

void subractOneForLongRef(Reference ref) {
  TALLOC_DEREF(ref, long) = TALLOC_DEREF(ref, long) - 1;
}

int
main(void)
{
  tallocInit();
  Reference test = TALLOC("main.test", int);   /* NOLINT */
  Reference test2 = TALLOC("main.test2", int); /* NOLINT */
  Reference test3 = TALLOC("main.test3", long); /* NOLINT */
  TALLOC_DEREF(test, int) = 1;
  TALLOC_DEREF(test2, int) = 2;
  TALLOC_DEREF(test3, long) = 3;
  printf("1: %d, 2: %d\n", TALLOC_DEREF(test, int), TALLOC_DEREF(test2, int));
  printReference(test2);
  tallocForEachRef(printReference);
  tallocForEachInstance(subractOneForLongRef, TALLOC_TYPE(long));
  printf("3: %ld\n", TALLOC_DEREF(test3, long));
  return EXIT_SUCCESS;
}
