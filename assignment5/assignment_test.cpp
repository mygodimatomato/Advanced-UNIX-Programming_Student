#include <stdio.h>
#include <stdlib.h>



int f1(int val){
  int num = 0;
  int *ptr = &num;

  printf("Value %d is at %p\n", val, &val);
  printf("%p\n", &num);
  printf("%p\n", &ptr);
  if (num == 0) {
    int val;
    val = 5;
    ptr = &val;
    printf("Value %d is at %p\n", val, &val);
  }

  return (*ptr + 1);
}
int main()
{
  int val = 5;
  // int *ptr_to_val;
  int tmp = f1(val);

  
  // printf("Value %d is at %p\n", *ptr_to_val, (void *)ptr_to_val);
  printf("Value %d is at %p\n", val, &val);
  printf("Value %d is at %p\n", tmp, &tmp);

  return 0;
}
