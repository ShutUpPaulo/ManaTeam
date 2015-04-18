#include <stdio.h>
#include <stdlib.h>

int dobra(int);
void dobra2(int*, int*, int*);


int main()
{
	int a, b,c;

	a = 2;
	b = 3;
	c = 5;
	
	a = dobra(a);
	b = dobra(b);
	c = dobra(c);

	printf("depois da primeira dobra:\n a: %d, b: %d, c: %d", a, b, c);

	dobra2(&a, &b, &c);

	printf("depois da segunda dobra:\n a: %d, b: %d, c: %d", a, b, c);

}

int dobra(int x)
{
	return x = x*x;
}

void dobra2(int * x, int * y, int * z)
{
	*x = (*x) * (*x);
	*y = (*y) * (*y);
	*z = (*z) * (*z);
}