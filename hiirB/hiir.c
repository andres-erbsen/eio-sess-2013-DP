#include <stdio.h>
#include <stdbool.h>
#define MAXX 100
#define MAXY 100
#define MAXT (201)
#define WRAP(n) (n%100000007)

int X, Y;
int hiir[MAXT][MAXX][MAXY][2];
bool takistus[MAXX][MAXY];


int main() {
	scanf("%d %d", &X, &Y);
	int i, j, t, s;
	char rida[101];
	for (i=0; i<X; ++i) {
		scanf("%s", rida);
		for (j=0; j<Y; ++j) takistus[i][j] = (rida[j] == 'X') ? 1 : 0;
	}

	hiir[1][1][0][1] = 1;
	hiir[1][0][1][0] = 1;

	for (t=2; t<MAXT; ++t) {
		for (i=0; i<X; ++i) {
			for (j=0; j<Y; ++j) {
				if (!takistus[i][j]) {
					if (i) hiir[t][i][j][1] = WRAP(hiir[t-1][i-1][j][1] + hiir[t-2][i-1][j][0]);
					if (j) hiir[t][i][j][0] = WRAP(hiir[t-1][i][j-1][0] + hiir[t-2][i][j-1][1]);
				}
			}
		}
	}
	for (t=0; t<MAXT; ++t) {
		int v = hiir[t][X-1][Y-1][0] + hiir[t][X-1][Y-1][1];
		if (v) printf("%d %d\n",t,v);
	}
}
