#include "talloc/talloc.h"
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
  Reference test = talloc("main.test", int);   /* NOLINT */
  Reference test2 = talloc("main.test2", int); /* NOLINT */
  return EXIT_SUCCESS;
}
