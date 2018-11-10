#include "io.h"
#include "sub.h"
#include "errcodes.h"

int main(void)
{
	setbuf(stdout, NULL);
	setbuf(stderr, NULL);

	int rc;
	int *a = NULL, *b = NULL, *c = NULL;
	size_t n = 0, m = 0, k = 0;

	if ((rc = read_arrays(&a, &n, &b, &m)) != SUCCESS)
		goto free_a_b;

	if ((rc = sub(a, n, b, m, &c, &k)) != SUCCESS)
		goto free_a_b_c;

	write_array(c, k);

free_a_b_c:
	free(c);
free_a_b:
	free(b);
	free(a);

	return rc;
}
