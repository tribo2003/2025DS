#include <iostream>
#include <vector>
#include <algorithm> // 用於 std::max

int jump(const std::vector<std::vector<int>>& leaves) {
    int maxBrokenLeaves = 0;
    int rows = leaves.size();
    int cols = leaves[0].size();

    // 檢查每一行
    for (int row = 0; row < rows; row++) {
        for (int i = 0, j = 0; i < cols; i++) {
            if (leaves[row][i] != 0) {
                if ((leaves[row][i] | leaves[row][j]) == 3) {
                    maxBrokenLeaves = std::max(maxBrokenLeaves, i - j - 1);
                }
                j = i; // 更新 j 為當前的 i
            }
        }
    }

    // 檢查每一列
    for (int col = 0; col < cols; col++) {
        for (int i = 0, j = 0; i < rows; i++) {
            if (leaves[i][col] != 0) {
                if ((leaves[i][col] | leaves[j][col]) == 3) {
                    maxBrokenLeaves = std::max(maxBrokenLeaves, i - j - 1);
                }
                j = i; // 更新 j 為當前的 i
            }
        }
    }

    return maxBrokenLeaves;
}

int main() {
    int rows, cols;
    std::cin >> rows >> cols;
    std::vector<std::vector<int>> leaves(rows, std::vector<int>(cols));

    // 讀取數據
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cin >> leaves[i][j];
        }
    }

    std::cout << jump(leaves) << std::endl;

    return 0;
}