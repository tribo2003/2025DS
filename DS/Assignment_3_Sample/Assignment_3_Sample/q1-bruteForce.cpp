#include <iostream>
#include <vector>
#include <climits>

using namespace std;

long long minimumSumOfAltitude(vector<int> &elevation) {
	long long result = LLONG_MAX;
	for (int i=0; i<elevation.size(); ++i) {
		int curAltitude = elevation[i];
		long long sum = 0;
		for (int j=i-1; j>=0; --j) {
			curAltitude = max(curAltitude, elevation[j]);
			sum += curAltitude;
		}
		curAltitude = elevation[i];
		for (int j=i; j<elevation.size(); ++j) {
			curAltitude = max(curAltitude, elevation[j]);
			sum += curAltitude;
		}
		result = min(result, sum);
	}
	return result;
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