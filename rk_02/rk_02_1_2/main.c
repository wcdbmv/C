#include <stdio.h>

#define N 128

void read_array(FILE *file, int *a, int *n)
{
	*n = 0;
	int tmp;
	while (fscanf(file, "%d", &tmp) == 1) // actually `!= EOF`
	{
		a[(*n)++] = tmp;
	}
}

void find_indices_min_max(int *a, int n, int *i_min, int *i_max)
{
	*i_min = *i_max = 0;
	for (int i = 0; i != n; ++i)
	{
		*i_min = a[i] < a[*i_min] ? i : *i_min;
		*i_max = a[i] > a[*i_max] ? i : *i_max;
	}
}

int pop(int *a, int *n, int i)
{
	int popped = a[i];
	for (int j = i; j < *n - 1; ++j)
	{
		a[j] = a[j + 1];
	}
	--*n;
	return popped;
}

void insert(int *a, int *n, int i, int val)
{
	for (int j = *n; j > i; --j)
	{
		a[j] = a[j - 1];
	}
	a[i] = val;
	++*n;
}

void insert_max_before_min(int *a, int n, int i_min, int i_max)
{
	if (i_min == i_max)
	{
		return;
	}
	
	int max = pop(a, &n, i_max);
	insert(a, &n, i_min, max);
}

void fprintf_array(FILE *file, int *a, int n)
{
	for (int i = 0; i != n; ++i)
	{
		fprintf(file, "%d ", a[i]);
	}
}

int main()
{
	FILE *f_in = fopen("input.txt", "r");
	FILE *f_out = fopen("output.txt", "w");
	
	if (f_in && f_out)
	{
		int a[N], n = 0;
		read_array(f_in, a, &n);
		
		int i_min = 0, i_max = 0;
		find_indices_min_max(a, n, &i_min, &i_max);
		
		insert_max_before_min(a, n, i_min, i_max);
		
		fprintf_array(f_out, a, n);
		
		fclose(f_in);
		fclose(f_out);
	}
	
	return 0;
}