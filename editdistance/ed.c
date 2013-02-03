#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>

#define DST_EQ  0
#define DST_ADD 1
#define DST_DEL 999
#define DST_SUB 1
#define DST_SWP 1

typedef unsigned int uint;

int main(int argc, char** argv) {
	uint i, j;
	if (argc != 3) printf("Usage: %s WORD1 WORD2\n", argv[0]);

	// FIXME: stringide alguses on tühik juurdemõeldav, indeksitest lahutada 1
	char* from = argv[1];
	char* to   = argv[2];
	uint M = 1 + strlen(from);
	uint N = 1 + strlen(to);

	uint** distance = (uint**) malloc(M*sizeof(uint*));
	char** operation = (char**) malloc(M*sizeof(char*)); // " DASW"
	for (i=0; i<M; i++) {
		distance[i] = (uint*) malloc(N*sizeof(uint));
		operation[i] = (char*) malloc(N*sizeof(char));
	}

	distance[0][0] = 0; // "" -> "" costs nothing
	operation[0][0] = ' ';
	for (i=1; i<M; ++i) {
		distance[i][0] = distance[i-1][0] + DST_DEL;
		operation[i][0] = 'D';
	}
	for (i=1; i<N; ++i) {
		distance[0][i] = distance[0][i-1] + DST_ADD;
		operation[0][i] = 'A';
	}

	for (j=1; j<N; ++j) {
		for (i=1; i<M; ++i) {
			char op = 'X';
			uint dst = UINT_MAX;
			#define possible(m,n,o,d) do {      \
				uint ndst = d + distance[m][n]; \
				if (ndst < dst) {               \
					dst = ndst;                 \
					op = o;                     \
				}                               \
			}                             while(0)
			if ( i>1 && j>1 && from[i-1] == to[j-1-1] && from[i-1-1] == to[j-1] ) possible(i-2, j-2, 'W', DST_SWP);
			if (from[i-1] == to[j-1]) possible(i-1, j-1, ' ', DST_EQ);
			possible(i-1, j-1, 'S', DST_SUB);
			possible(i-1, j  , 'D', DST_DEL);
			possible(i  , j-1, 'A', DST_ADD);
			operation[i][j] = op;
			distance[i][j] = dst;
		}
	}

	printf("   ");
	for (j=0; j<N-1; ++j) printf("  %c", to[j]);
	printf("\n");
	for (i=0; i<M; ++i) {
		printf("%c", i?from[i-1]:' ');
		for (j=0; j<N; ++j) {
			printf(" %d%c", distance[i][j], operation[i][j]);
		}
		printf("\n");
	}

	for (i=0; i<M; i++) {
		free(distance[i]);
		free(operation[i]);
	}
	free(distance);
	free(operation);
}
