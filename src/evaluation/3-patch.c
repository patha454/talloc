#include "talloc/talloc.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void null_transform(Reference ref)
{
  return;
}

void widen_transform(Reference ref)
{
  long* wider = malloc(sizeof(*wider));
  *wider = TALLOC_DEREF(ref, int);
  TALLOC_REF_UPDATE(ref, wider);
}

int main(int argc, char** argv)
{
  if (argc < 2) {
    fprintf(stderr, "Usage: ./2-patch <item count");
  }
  char label[32] = { 0 };
  int items = atoi(argv[1]);
  for (int i = 0; i < 100000; i++)
  {
    // Allocate some "chaff" to populate mess the tracking structure.
    sprintf(label, "main.%d", i);
    // We don't need to keep the references for this experiment.
    TALLOC(label, unsigned long);
  }
  for (int i = 0; i < items; i++)
  {
    // We'll be patching these int instances.
    sprintf(label, "main.int.%d", i);
    TALLOC(label, int);
  }
  tallocForEachInstance(widen_transform, TALLOC_TYPE(int));
}
