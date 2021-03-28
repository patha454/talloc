#include "talloc/reference.h"
#include "talloc/talloc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct TkRefTree* TkRefTree;

void
tkRefTreeForEach(TkRefTree tree, void (*lambda)(Reference));

void
printReference(Reference ref)
{
  printf("[Reference ID 0x%llx Type <0x%llx>]\n",
         tkReferenceId(ref),
         tkReferenceType(ref));
}

void
subractOneForLongRef(Reference ref)
{
  TALLOC_DEREF(ref, long) = TALLOC_DEREF(ref, long) - 1;
}

void
soleObjectTest()
{
  printf("Traverse (empty) tracking structure:\n");
  tallocForEachRef(printReference);
  printf("\n");
  printf("Allocating a sole object...\n\n");
  Reference test = TALLOC("main.test", int);
  printf("Traversal after allocaing a sole object:\n");
  tallocForEachRef(printReference);
  printf("\n");
  printf("Freeing the sole object...\n\n");
  tallocFree(test);
  printf("Traversal after freeing the sole object:\n");
  tallocForEachRef(printReference);
  printf("\n");
}

void
childTest()
{
  printf("Allocating a two objects (left child)...\n");
  Reference testRoot = TALLOC("childTest.testRoot", int);
  Reference leftChild = TALLOC("childTest.testleftChild", int);
  printf("Traversal after allocaing two objects:\n");
  tallocForEachRef(printReference);
  printf("Deleting child element...\n\n");
  tallocFree(leftChild);
  printf("Traversal after deleting child:\n");
  tallocForEachRef(printReference);
  printf("Reallocating left child...\n\n");
  leftChild = TALLOC("childTest.leftChild", int);
  printf("Traversal after reallocating left child:\n");
  tallocForEachRef(printReference);
  printf("Deleting root object...\n\n");
  tallocFree(testRoot);
  printf("Traversal after deleting root object:\n");
  tallocForEachRef(printReference);
  printf("Freeing new root object...\n");
  tallocFree(leftChild);
  printf("Traversal after deleting new root object:\n");
  tallocForEachRef(printReference);
  printf("\n");
}

void
complexTest()
{
  printf("Allocating five objects...\n\n");
  Reference c = TALLOC("complexTest.c", int);
  Reference e = TALLOC("complexTest.e", long);
  Reference b = TALLOC("complexTest.b", Reference);
  Reference a = TALLOC("complexTest.a", char);
  Reference d = TALLOC("complexTest.d", char[6]);
  printf("Traversal after allocating five objects...\n\n");
  tallocForEachRef(printReference);
  printf("Deleting %lx and %lx...\n\n", tkReferenceId(b), tkReferenceId(d));
  tallocFree(d);
  tallocFree(b);
  printf("Traversal after deleting two objects:\n");
  tallocForEachRef(printReference);
}

int
main(void)
{
  printf("Initialising Talloc...\n\n");
  tallocInit();
  soleObjectTest();
  childTest();
  complexTest();
  return EXIT_SUCCESS;
}
