#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int mintotal(vector<int>& elevation) {
    int n = elevation.size();
    if (n == 0) return 0; // 空陣列

    // 找出 elevation 中的最大值及其索引
    auto maxIt = max_element(elevation.begin(), elevation.end());
    int maxElevation = *maxIt;
    int maxIndex = distance(elevation.begin(), maxIt);

    vector<long long> total; // 使用 long long 避免溢出

    // i 是爬升點
    for (int i = 0; i < n; ++i) {
        vector<int> altitude(n, 0); // 初始化 altitude 為 0

        // 將 elevation[i] 設為爬升點
        altitude[i] = elevation[i];
        int current = altitude[i];

        // 從開頭往爬升點計算 altitude
        for (int j = 0; j < i; ++j) {
            current = min(current, elevation[j]);
            altitude[j] = max(current, elevation[j]);
            current = altitude[j];
        }

        // 從爬升點往後計算 altitude
        current = altitude[i];
        for (int j = i + 1; j < n; ++j) {
            current = max(current, elevation[j]);
            altitude[j] = min(current, maxElevation);
            current = altitude[j];
        }

        // 計算總和
        long long sum = 0;
        for (int j = 0; j < n; ++j) {
            sum += altitude[j];
        }

        // 將總和儲存到 total 陣列中
        total.push_back(sum);

        // 輸出調試信息
        cout << "Pull-up at " << i << ": altitude = ";
        for (int j = 0; j < n; ++j) {
            cout << altitude[j] << " ";
        }
        cout << "sum = " << sum << endl;
    }

    // 找到 total 中的最小值
    long long minimum = *min_element(total.begin(), total.end());
    return (int)minimum; // 將結果轉回 int
}

int main() {
    int n;
    cin >> n;

    vector<int> elevation(n);
    for (int i = 0; i < n; i++) {
        cin >> elevation[i];
    }

    cout << mintotal(elevation) << endl;
    return 0;
}