#include <iostream>
#include <vector>
#include <algorithm> // 用於 std::max

int jump(const std::vector<int>& leaves) {
    int maxBrokenLeaves = 0;
    int j = 0;
    int leavesSize = leaves.size();

    for (int i = 0; i < leavesSize; i++) {
        if (leaves[i] != 0) {
            if ((leaves[i] | leaves[j]) == 3) {
                maxBrokenLeaves = std::max(maxBrokenLeaves, i - j - 1);
            }
            j = i;
        }
    }
    return maxBrokenLeaves;
}

int main() {
    int leavesSize;
    std::cin >> leavesSize; // 使用 C++ 的標準輸入
    std::vector<int> leaves(leavesSize);

    for (int i = 0; i < leavesSize; i++) {
        std::cin >> leaves[i]; // 使用 C++ 的標準輸入
    }

    std::cout << jump(leaves) << std::endl; // 使用 C++ 的標準輸出
    return 0;
}