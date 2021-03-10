#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef unsigned long long int _num;

_num *cache, size, next, n;

void termination(int nothing) {
    printf("Last n tested: %llu\n", n);
	exit(0);
}

/* Saves a value v in cache for faster retrieval */
void save(_num v) {
	if (next >= size - 1) {
		size *= 2;
		cache = realloc(cache, sizeof(_num) * size);
	}

	*(cache + next) = v;
	next++;
}

/* Computes the n-th number of the sequence using the cache */
_num q(_num n) {
	_num *dest = (cache - 1) + n;
	if (dest < cache) {
		printf("Failed at %llu\n", n);
		exit(0);
	}
	return *dest;
}

int main() {
	signal(SIGINT, termination);

	size = 5;
	cache = calloc(size, sizeof(_num));
	next = 0;

	/* Starting values */
	save(1);
	save(1);

	for (n = 3;; n++) {
		if (n % 1000000000 == 0)
			printf("%llu\n", n / 1000000000);
		save(q(n - q(n - 1)) + q(n - q(n - 2)));
	}

	return 0;
}
