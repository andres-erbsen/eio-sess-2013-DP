#include "stdio.h"
#include "limits.h"
#define MAXN 55

int cut[MAXN];
int cost[MAXN][MAXN]; // cost for cutting stick from cut a for d cuts

int main() {
	int l;
	while (1) {
		int i=0, n=0, a=0, d=0;
		scanf("%d",&l);
		if (l == 0) break;
		scanf("%d",&n);
		n += 2;

		cut[0] = 0;
		for (i=1; i<n-1; ++i) {
			scanf("%d", &cut[i]);
			cost[i-1][1] = 0;
		}
		cut[n-1] = l;
		cost[n-2][1] = 0;
		
		// cost(a,d)
		for (d=2; d<=n; ++d) {
			for (a=0; a<n-d; ++a) {
				int c = INT_MAX;
				for (i=1; i<d; ++i) {
					int nc = cost[a][i] + cost[a+i][d-i];
					if (nc < c) c = nc;
				}
				c += cut[a+d] - cut[a];
				cost[a][d] = c;
				// printf("cost(%d, %d) = %d; ", a, d, c);
			}
			// printf("\n");
		}
		printf("The minimum cutting is %d.\n", cost[0][n-1]);
	}
}
