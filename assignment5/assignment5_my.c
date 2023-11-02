#include <stdio.h>
#include <stdlib.h>



int f1 (int *val, int **pptr) {

  *pptr = val;
  return (**pptr + 1); // this is a int
}

int main()
{
  int val = 5;
  int *ptr_to_val;
  int tmp = f1(&val, &ptr_to_val);

  
  printf("Value %d is at %p\n", *ptr_to_val, (void *)ptr_to_val);
  // printf("Value %d is at %p\n", val, &val);
  // printf("Value %d is at %p\n", tmp, &tmp);

  return 0;
}
