#include <stdio.h>
#include <limits.h>

#define MAX_N 5000
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef long long LL;

int main() {
	int n, start, end;
	int elevation[MAX_N];
	int st[MAX_N], sz = 0;  // monotonic stack
	LL leftDive[MAX_N];     // minimum sum of altitude when diving from left to i
	LL rightClimb[MAX_N];   // minimum sum of altitude when climbing from i to right
	LL leftSum[MAX_N];		// minimim sum of altitude of one pull-up before i
	LL rightSum[MAX_N];		// minimim sum of altitude of one pull-up after i

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &elevation[i]);
		leftSum[i] = rightSum[i] = LLONG_MAX;
	}

	// Compute leftDive & leftSum
	for (int i = 0; i < n; i++) { // i is pull-up point
		while (sz && elevation[st[sz-1]] <= elevation[i]) {
			sz--;
		}
		int prevHill = (sz) ? st[sz-1] : -1;
		leftDive[i] = (LL)elevation[i] * (i - prevHill)
				    + (prevHill == -1 ? 0LL : leftDive[prevHill]);
		st[sz++] = i;

		LL sum = 0;
		int alt = elevation[i];
		// compute the minimum sum of altitude of one pull-up at i then climb to j
		// brute forcing is faster than using a stack here
		for (int j = i; j < n; j++) { // j is descend point
			alt = max(alt, elevation[j]);
			sum += alt;
			leftSum[j] = min(leftSum[j], leftDive[i] - elevation[i] + sum);
		}
	}

	// Compute rightClimb & rightSum
	sz = 0;  // reset the stack for reuse
	for (int i = n-1; i >= 0; i--) { // i is pull-up point
		while (sz && elevation[st[sz-1]] <= elevation[i]) {
			sz--;
		}
		int nextHill = (sz) ? st[sz-1] : n;
		rightClimb[i] = (LL)elevation[i] * (nextHill - i)
				      + (nextHill == n ? 0LL : rightClimb[nextHill]);
		st[sz++] = i;

		LL sum = 0;
		int alt = elevation[i];
		// compute the minimum sum of altitude when descending from j to i then pull-up at i
		for (int j = i; j >= 0; j--) { // j is descend point
			alt = max(alt, elevation[j]);
			sum += alt;
			rightSum[j] = min(rightSum[j], rightClimb[i] - elevation[i] + sum);
		}
	}

	// Find the minimum sum
	LL minSum = LLONG_MAX;
	for (int i = 0; i < n; i++) { // i is descend point
		minSum = min(minSum, leftSum[i] - elevation[i] + rightSum[i]);
	}
	printf("%lld\n", minSum);

	return 0;
}