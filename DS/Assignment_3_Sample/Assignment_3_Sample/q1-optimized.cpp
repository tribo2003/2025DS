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

LL minimumSumOfAltitude(vector<int> &elevation) {
	int n = elevation.size();
	stack<hill_t> hills;		// stack to store last higher hill, its content is always sorted in decreasing height
	vector<LL> diveSum(n, 0);   // minimum sum of altitude when diving from left to i
	vector<LL> climbSum(n, 0);  // minimum sum of altitude when climbing from i to right

	// Diving, calculate from left to right
	for (int i=0; i<n; ++i) {
		// Pop all hills that are lower than the current elevation
		while (!hills.empty() && hills.top().height <= elevation[i]) {
			hills.pop();
		}
		int prevHill = (hills.empty()) ? -1 : hills.top().position;
		diveSum[i] = (LL)elevation[i] * (i - prevHill)				// keep the current elevation until last higher hill
				   + (prevHill == -1 ? 0LL : diveSum[prevHill]);    // reuse the minimum sum of altitude from last higher hill
		hills.push({elevation[i], i});
	}

	// Clear the stack for reusing
	while (!hills.empty()) {
		hills.pop();
	}

	// Climbing, calculate from right to left
	for (int i=n-1; i>=0; --i) {
		// Pop all hills that are lower than the current elevation
		while (!hills.empty() && hills.top().height <= elevation[i]) {
			hills.pop();
		}
		int nextHill = (hills.empty()) ? n : hills.top().position;
		climbSum[i] = (LL)elevation[i] * (nextHill - i)				// keep the current elevation until next higher hill
				    + (nextHill == n ? 0LL : climbSum[nextHill]);	// reuse the minimum sum of altitude from next higher hill
		hills.push({elevation[i], i});
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
	for (auto i: elevation) {
		cout << setw(COL_WIDTH) << i << " ";
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
		// subtract elevation[i] because it is counted twice
		// "a + b - c" could overflow at the first step, so we use "a - c + b" instead
		minSum = min(minSum, diveSum[i] - elevation[i] + climbSum[i]);
	}

	return minSum;
}

int main() {
	// ios::sync_with_stdio(0);
	// cin.tie(0);

	int n;
	cin >> n;
	vector<int> elevation(n);
	for (int i = 0; i < n; i++) {
		cin >> elevation[i];
	}

	cout << minimumSumOfAltitude(elevation);

	return 0;
}