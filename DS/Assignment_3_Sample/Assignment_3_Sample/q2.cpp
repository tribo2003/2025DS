#include <iostream>
#include <stack>
#include <vector>
#include <climits>
#include <iomanip>

// Uncomment the following line to print debug messages
// #define DEBUG 1
#define COL_WIDTH 3

typedef long long LL;

using namespace std;

typedef struct hill {
	int height;
	int position;
} hill_t;

LL minimumSumOfAltitudeAtRange(vector<int> &terrain, int start, int end) {
	int n = end - start;

	if (n <= 0) {
		return LLONG_MAX;
	} else if (n == 1) {
		return terrain[start];
	}

	stack<hill_t> hills1, hills2;
	vector<LL> diveSum(n, 0);
	vector<LL> climbSum(n, 0);

	// Diving, calculate from left to right
	for (int i=0; i<n; ++i) {
		while (!hills1.empty() && hills1.top().height <= terrain[start + i]) {
			hills1.pop();
		}
		int prevHill = (hills1.empty()) ? -1 : hills1.top().position;
		diveSum[i] = (LL)terrain[start + i] * (i - prevHill)
				   + (prevHill == -1 ? 0LL : diveSum[prevHill]);
		hills1.push({terrain[start + i], i});
	}

	// Climbing, calculate from right to left
	for (int i=n-1; i>=0; --i) {
		while (!hills2.empty() && hills2.top().height <= terrain[start + i]) {
			hills2.pop();
		}
		int nextHill = (hills2.empty()) ? n : hills2.top().position;
		climbSum[i] = (LL)terrain[start + i] * (nextHill - i)
				    + (nextHill == n ? 0LL : climbSum[nextHill]);
		hills2.push({terrain[start + i], i});
	}

#ifdef DEBUG
	cout << " dive:";
	for (auto i : diveSum) {
		cout << setw(COL_WIDTH) << i << " ";
	}
	cout << "\nclimb:";
	for (auto i : climbSum) {
		cout << setw(COL_WIDTH) << i << " ";
	}
	cout << "\n deck:";
	for (int i=0; i<n; ++i) {
		cout << setw(COL_WIDTH) << terrain[start+ i] << " ";
	}
	cout << "\nindex:";
	for (int i=0; i<n; ++i) {
		cout << setw(COL_WIDTH) << i << " ";
	}
	cout << "\n";
#endif

	// Calculate the minimum sum of altitude
	LL minSum = LLONG_MAX;
	for (int i=0; i<n; ++i) {
		minSum = min(minSum, diveSum[i] - terrain[start + i] + climbSum[i]);
	}

	return minSum;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;
	vector<int> terrain(n);
	for (int i = 0; i < n; i++) {
		cin >> terrain[i];
	}

	LL minSum = minimumSumOfAltitudeAtRange(terrain, 0, n);
	for (int i=1; i<n; ++i) {  // i is descend point
		LL l, r;
		l = minimumSumOfAltitudeAtRange(terrain, 0, i);
		r = minimumSumOfAltitudeAtRange(terrain, i, n);
		minSum = min(minSum, l + r);
	}

	cout << minSum;

	return 0;
}