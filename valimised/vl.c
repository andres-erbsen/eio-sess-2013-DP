#include <stdio.h>
#include <stdbool.h>
#define MAXN 1000

int N;
int mehi[MAXN];
bool possible[MAXN][MAXN];



int main() {
	scanf("%d", &N);
	int i, j, S=0;
	for (i=0; i<N; ++i) {
		scanf("%d", &mehi[i]);
		S += mehi[i];
	}
	possible[0][0] = 1;
	possible[0][mehi[0]] = 1;

	for (i=1; i<N; ++i) {
		for (j=0; j<=S/2; j++) {
			if ( possible[i-1][j] ) {
				possible[i][j] = 1;
				possible[i][j+mehi[i]] = 1;
			}
		}
	}

	if (S/2 + S/2 == S && possible[N-1][S/2] ) {
		printf("EI\n");
		j = S/2;
		bool first = 1;
		for (i=N-1; i>0; --i) {
			if ( possible[i-1][j-mehi[i]] ) {
				if (!first) printf(" ");
				first = 0;
				printf("%d",mehi[i]);
				j = j-mehi[i];
			}
		}
		printf("\n");
	} else {
		printf("JAH\n");
		int m=0;
		for (j=0; j<=S/2; ++j) if (possible[N-1][j]) m = j;
		printf("%d\n", S-2*m);
	}
}
