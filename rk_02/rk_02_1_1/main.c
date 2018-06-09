#include <stdio.h>

#define N 128

void read_arrays(FILE *f_in, int *a, int *b, int *n)
{
	fscanf(f_in, "%d", n);
	
	for (int i = 0; i != *n; ++i)
	{
		fscanf(f_in, "%d", a + i);
	}
	
	for (int i = 0; i != *n; ++i)
	{
		fscanf(f_in, "%d", b + i);
	}
}

void bitwise_and(int *a, int *b, int *c, int n)
{
	for (int i = 0; i != n; ++i)
	{
		c[i] = a[i] & b[i];
	}
}

void fprintf_array(FILE *f_out, int *a, int n)
{
	for (int i = 0; i != n; ++i)
	{
		fprintf(f_out, "%d", a[i]);
	}
}

int main()
{	
	FILE *f_in = fopen("input.txt", "r");
	FILE *f_out = fopen("output.txt", "w");
	
	if (f_in && f_out)
	{
		int a[N], b[N], c[N], n = 0;
		
		read_arrays(f_in, a, b, &n);
		bitwise_and(a, b, c, n);
		fprintf_array(f_out, c, n);
		
		
		fclose(f_in);
		fclose(f_out);
	}
	
	
	return 0;
}