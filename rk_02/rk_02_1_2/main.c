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

void insert_max_before_min(int *a, int n, int i_min, int i_max)
{
	if (i_min == i_max)
	{
		return;
	}
	
	int max = a[i_max];
	
	if (i_min < i_max)
	{
		for (int i = i_max; i > i_min; --i)
		{
			a[i] = a[i - 1];
		}
		a[i_min] = max;
	}
	else
	{
		for (int i = i_max; i < i_min - 1; ++i)
		{
			a[i] = a[i + 1];
		}
		a[i_min - 1] = max;
	}
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