#include <stdio.h>
#include <stdlib.h>

int* f1(int* val)
{
	return &(*val);
}

int main() {
	int *val = malloc(sizeof(int));
	*val = 5;
	int* valp = f1(val);
	printf("Value %i is at %p\n", *val, valp);
	// printf("%p\n", val);
}
