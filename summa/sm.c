#include <stdio.h>
#define MAXM 100
#define MAXN 100
#define max(a,b) ((a>b)?a:b)

int M, N;
int tabel[MAXM][MAXN];
int summa[MAXM][MAXN];

int main() {
	scanf("%d %d", &M, &N);
	int i, j;
	for (i=0; i<M; ++i) {
		for (j=0; j<N; ++j) {
			scanf("%d",&tabel[i][j]);
			summa[i][j] = 0;
		}
	}
	summa[M-1][0] = tabel[M-1][0];
	for (j=1; j<N; j++) summa[M-1][j] = tabel[M-1][j] + summa[M-1][j-1];

	for (i=M-2; i>=0; --i) {
		summa[i][0] = tabel[i][0] + summa[i+1][0];
		for (j=1; j<N; ++j) {
			summa[i][j] = tabel[i][j] + max( summa[i+1][j], summa[i][j-1] );
		}
	}
	printf("%d\n",summa[0][N-1]);
}
